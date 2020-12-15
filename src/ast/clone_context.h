// Copyright 2020 The Tint Authors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef SRC_AST_CLONE_CONTEXT_H_
#define SRC_AST_CLONE_CONTEXT_H_

#include <functional>
#include <unordered_map>
#include <vector>

#include "src/ast/traits.h"
#include "src/castable.h"
#include "src/source.h"
#include "src/symbol.h"

namespace tint {
namespace ast {

class Module;

/// CloneContext holds the state used while cloning AST nodes and types.
class CloneContext {
 public:
  /// Constructor
  /// @param to the target module to clone into
  /// @param from the source module to clone from
  CloneContext(Module* to, Module const* from);

  /// Destructor
  ~CloneContext();

  /// Clones the Node or type::Type `a` into the module #mod if `a` is not
  /// null. If `a` is null, then Clone() returns null. If `a` has been cloned
  /// already by this CloneContext then the same cloned pointer is returned.
  ///
  /// Clone() may use a function registered with ReplaceAll() to create a
  /// transformed version of the object. See ReplaceAll() for more information.
  ///
  /// The Node or type::Type `a` must be owned by the module #src.
  ///
  /// @note Semantic information such as resolved expression type and intrinsic
  /// information is not cloned.
  /// @param a the `Node` or `type::Type` to clone
  /// @return the cloned node
  template <typename T>
  T* Clone(T* a) {
    // If the input is nullptr, there's nothing to clone - just return nullptr.
    if (a == nullptr) {
      return nullptr;
    }

    // See if we've already cloned this object - if we have return the
    // previously cloned pointer.
    // If we haven't cloned this before, try cloning using a replacer transform.
    if (auto* c = LookupOrTransform(a)) {
      return static_cast<T*>(c);
    }

    // First time clone and no replacer transforms matched.
    // Clone with T::Clone().
    auto* c = a->Clone(this);
    cloned_.emplace(a, c);
    return static_cast<T*>(c);
  }

  /// Clones the Source `s` into `mod`
  /// TODO(bclayton) - Currently this 'clone' is a shallow copy. If/when
  /// `Source.File`s are owned by the `Module` this should make a copy of the
  /// file.
  /// @param s the `Source` to clone
  /// @return the cloned source
  Source Clone(const Source& s) const { return s; }

  /// Clones the Symbol `s` into `mod`
  ///
  /// The Symbol `s` must be owned by the module #src.
  ///
  /// @param s the Symbol to clone
  /// @return the cloned source
  Symbol Clone(const Symbol& s) const;

  /// Clones each of the elements of the vector `v` into the module #mod->
  ///
  /// All the elements of the vector `v` must be owned by the module #src.
  ///
  /// @param v the vector to clone
  /// @return the cloned vector
  template <typename T>
  std::vector<T> Clone(const std::vector<T>& v) {
    std::vector<T> out;
    out.reserve(v.size());
    for (auto& el : v) {
      out.emplace_back(Clone(el));
    }
    return out;
  }

  /// ReplaceAll() registers `replacer` to be called whenever the Clone() method
  /// is called with a type that matches (or derives from) the type of the
  /// second parameter of `replacer`.
  ///
  /// `replacer` must be function-like with the signature:
  ///   `T* (CloneContext*, T*)`
  ///  where `T` is a type deriving from CastableBase.
  ///
  /// If `replacer` returns a nullptr then Clone() will attempt the next
  /// registered replacer function that matches the object type. If no replacers
  /// match the object type, or all returned nullptr then Clone() will call
  /// `T::Clone()` to clone the object.
  ///
  /// Example:
  ///
  /// ```
  ///   // Replace all ast::UintLiterals with the number 42
  ///   CloneCtx ctx(&out, in)
  ///     .ReplaceAll([&] (CloneContext* ctx, ast::UintLiteral* l) {
  ///       return ctx->mod->create<ast::UintLiteral>(ctx->Clone(l->source()),
  ///                                                 ctx->Clone(l->type()),
  ///                                                 42);
  ///     }).Clone();
  /// ```
  ///
  /// @param replacer a function or function-like object with the signature
  ///        `T* (CloneContext*, T*)`, where `T` derives from CastableBase
  /// @returns this CloneContext so calls can be chained
  template <typename F>
  CloneContext& ReplaceAll(F replacer) {
    using TPtr = traits::ParamTypeT<F, 1>;
    using T = typename std::remove_pointer<TPtr>::type;
    transforms_.emplace_back([=](CastableBase* in) {
      auto* in_as_t = in->As<T>();
      return in_as_t != nullptr ? replacer(this, in_as_t) : nullptr;
    });
    return *this;
  }

  /// Clone performs the clone of the entire module #src to #mod.
  void Clone();

  /// The target module to clone into.
  Module* const mod;

  /// The source module to clone from.
  Module const* const src;

 private:
  using Transform = std::function<CastableBase*(CastableBase*)>;

  CloneContext(const CloneContext&) = delete;
  CloneContext& operator=(const CloneContext&) = delete;

  /// LookupOrTransform is the template-independent logic of Clone().
  /// This is outside of Clone() to reduce the amount of template-instantiated
  /// code.
  CastableBase* LookupOrTransform(CastableBase* a) {
    // Have we seen this object before? If so, return the previously cloned
    // version instead of making yet another copy.
    auto it = cloned_.find(a);
    if (it != cloned_.end()) {
      return it->second;
    }

    // Attempt to clone using the registered replacer functions.
    for (auto& f : transforms_) {
      if (CastableBase* c = f(a)) {
        cloned_.emplace(a, c);
        return c;
      }
    }

    // No luck, Clone() will have to call T::Clone().
    return nullptr;
  }

  std::unordered_map<CastableBase*, CastableBase*> cloned_;
  std::vector<Transform> transforms_;
};

}  // namespace ast
}  // namespace tint

#endif  // SRC_AST_CLONE_CONTEXT_H_

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

#include "src/ast/clone_context.h"

#include "src/ast/module.h"

namespace tint {
namespace ast {

CloneContext::CloneContext(Module* to, Module const* from)
    : mod(to), src(from) {}
CloneContext::~CloneContext() = default;

Symbol CloneContext::Clone(const Symbol& s) const {
  return mod->RegisterSymbol(src->SymbolToName(s));
}

void CloneContext::Clone() {
  src->Clone(this);
}

}  // namespace ast
}  // namespace tint

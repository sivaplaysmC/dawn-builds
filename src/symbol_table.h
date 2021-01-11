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

#ifndef SRC_SYMBOL_TABLE_H_
#define SRC_SYMBOL_TABLE_H_

#include <string>
#include <unordered_map>

#include "src/symbol.h"

namespace tint {

/// Holds mappings from symbols to their associated string names
class SymbolTable {
 public:
  /// Constructor
  SymbolTable();
  /// Copy constructor
  SymbolTable(const SymbolTable&);
  /// Move Constructor
  SymbolTable(SymbolTable&&);
  /// Destructor
  ~SymbolTable();

  /// Copy assignment
  /// @param other the symbol table to copy
  /// @returns the new symbol table
  SymbolTable& operator=(const SymbolTable& other);
  /// Move assignment
  /// @param other the symbol table to move
  /// @returns the symbol table
  SymbolTable& operator=(SymbolTable&& other);

  /// Registers a name into the symbol table, returning the Symbol.
  /// @param name the name to register
  /// @returns the symbol representing the given name
  Symbol Register(const std::string& name);

  /// Returns the symbol for the given `name`
  /// @param name the name to lookup
  /// @returns the symbol for the name or symbol::kInvalid if not found.
  Symbol GetSymbol(const std::string& name) const;

  /// Returns the name for the given symbol
  /// @param symbol the symbol to retrieve the name for
  /// @returns the symbol name or "" if not found
  std::string NameFor(const Symbol symbol) const;

 private:
  // The value to be associated to the next registered symbol table entry.
  uint32_t next_symbol_ = 1;

  std::unordered_map<Symbol, std::string> symbol_to_name_;
  std::unordered_map<std::string, Symbol> name_to_symbol_;
};

}  // namespace tint

#endif  // SRC_SYMBOL_TABLE_H_

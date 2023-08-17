# Copyright 2023 The Tint Authors.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

################################################################################
# File generated by tools/src/cmd/gen
# using the template:
#   tools/src/cmd/gen/build/BUILD.cmake.tmpl
#
# Do not modify this file directly
################################################################################

if(TINT_BUILD_IR)
################################################################################
# Target:    tint_lang_core_ir_transform
# Kind:      lib
# Condition: TINT_BUILD_IR
################################################################################
tint_add_target(tint_lang_core_ir_transform lib
  lang/core/ir/transform/add_empty_entry_point.cc
  lang/core/ir/transform/add_empty_entry_point.h
  lang/core/ir/transform/bgra8unorm_polyfill.cc
  lang/core/ir/transform/bgra8unorm_polyfill.h
  lang/core/ir/transform/binary_polyfill.cc
  lang/core/ir/transform/binary_polyfill.h
  lang/core/ir/transform/binding_remapper.cc
  lang/core/ir/transform/binding_remapper.h
  lang/core/ir/transform/block_decorated_structs.cc
  lang/core/ir/transform/block_decorated_structs.h
  lang/core/ir/transform/builtin_polyfill.cc
  lang/core/ir/transform/builtin_polyfill.h
  lang/core/ir/transform/demote_to_helper.cc
  lang/core/ir/transform/demote_to_helper.h
  lang/core/ir/transform/multiplanar_external_texture.cc
  lang/core/ir/transform/multiplanar_external_texture.h
  lang/core/ir/transform/shader_io.cc
  lang/core/ir/transform/shader_io.h
  lang/core/ir/transform/std140.cc
  lang/core/ir/transform/std140.h
)

tint_target_add_dependencies(tint_lang_core_ir_transform lib
  tint_api_common
  tint_api_options
  tint_lang_core
  tint_lang_core_constant
  tint_lang_core_type
  tint_utils_containers
  tint_utils_diagnostic
  tint_utils_ice
  tint_utils_id
  tint_utils_macros
  tint_utils_math
  tint_utils_memory
  tint_utils_reflection
  tint_utils_result
  tint_utils_rtti
  tint_utils_symbol
  tint_utils_text
  tint_utils_traits
)

if (TINT_BUILD_IR)
  tint_target_add_dependencies(tint_lang_core_ir_transform lib
    tint_lang_core_ir
  )
endif(TINT_BUILD_IR)

endif(TINT_BUILD_IR)
if(TINT_BUILD_IR)
################################################################################
# Target:    tint_lang_core_ir_transform_test
# Kind:      test
# Condition: TINT_BUILD_IR
################################################################################
tint_add_target(tint_lang_core_ir_transform_test test
  lang/core/ir/transform/add_empty_entry_point_test.cc
  lang/core/ir/transform/bgra8unorm_polyfill_test.cc
  lang/core/ir/transform/binary_polyfill_test.cc
  lang/core/ir/transform/binding_remapper_test.cc
  lang/core/ir/transform/block_decorated_structs_test.cc
  lang/core/ir/transform/builtin_polyfill_test.cc
  lang/core/ir/transform/demote_to_helper_test.cc
  lang/core/ir/transform/helper_test.h
  lang/core/ir/transform/multiplanar_external_texture_test.cc
  lang/core/ir/transform/std140_test.cc
)

tint_target_add_dependencies(tint_lang_core_ir_transform_test test
  tint_api_common
  tint_api_options
  tint_lang_core
  tint_lang_core_constant
  tint_lang_core_type
  tint_utils_containers
  tint_utils_diagnostic
  tint_utils_ice
  tint_utils_id
  tint_utils_macros
  tint_utils_math
  tint_utils_memory
  tint_utils_reflection
  tint_utils_result
  tint_utils_rtti
  tint_utils_symbol
  tint_utils_text
  tint_utils_traits
)

tint_target_add_external_dependencies(tint_lang_core_ir_transform_test test
  "gtest"
)

if (TINT_BUILD_IR)
  tint_target_add_dependencies(tint_lang_core_ir_transform_test test
    tint_lang_core_ir
    tint_lang_core_ir_transform
  )
endif(TINT_BUILD_IR)

endif(TINT_BUILD_IR)
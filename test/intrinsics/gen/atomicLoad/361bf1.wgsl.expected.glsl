SKIP: FAILED

#version 310 es
precision mediump float;

groupshared uint arg_0;

void atomicLoad_361bf1() {
  uint atomic_result = 0u;
  InterlockedOr(arg_0, 0, atomic_result);
  uint res = atomic_result;
}

struct tint_symbol_1 {
  uint local_invocation_index;
};

void compute_main_inner(uint local_invocation_index) {
  {
    uint atomic_result_1 = 0u;
    InterlockedExchange(arg_0, 0u, atomic_result_1);
  }
  GroupMemoryBarrierWithGroupSync();
  atomicLoad_361bf1();
}

layout(local_size_x = 1, local_size_y = 1, local_size_z = 1) in;
void compute_main(tint_symbol_1 tint_symbol) {
  compute_main_inner(tint_symbol.local_invocation_index);
  return;
}
void main() {
  tint_symbol_1 inputs;
  inputs.local_invocation_index = uint(gl_LocalInvocationIndex);
  compute_main(inputs);
}


Error parsing GLSL shader:
ERROR: 0:4: '' :  syntax error, unexpected IDENTIFIER
ERROR: 1 compilation errors.  No code generated.




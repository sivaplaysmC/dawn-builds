SKIP: FAILED

#version 310 es
precision mediump float;


uvec3 tint_symbol = uvec3(0u, 0u, 0u);
layout (binding = 2) buffer ResultMatrix_1 {
  float numbers[];
} resultMatrix;

float binaryOperation_f1_f1_(inout float a, inout float b) {
  float x_26 = 0.0f;
  float x_13 = b;
  if ((x_13 == 0.0f)) {
    return 1.0f;
  }
  float x_21 = b;
  if (!((round((x_21 - (2.0f * floor((x_21 / 2.0f))))) == 1.0f))) {
    float x_29 = a;
    float x_31 = b;
    x_26 = pow(abs(x_29), x_31);
  } else {
    float x_34 = a;
    float x_36 = a;
    float x_38 = b;
    x_26 = (sign(x_34) * pow(abs(x_36), x_38));
  }
  return x_26;
}

void main_1() {
  int index = 0;
  int a_1 = 0;
  float param = 0.0f;
  float param_1 = 0.0f;
  uint x_54 = tint_symbol.x;
  index = int(x_54);
  a_1 = -10;
  int x_63 = index;
  param = -4.0f;
  param_1 = -3.0f;
  float x_68 = binaryOperation_f1_f1_(param, param_1);
  resultMatrix.numbers[x_63] = x_68;
  return;
}

struct tint_symbol_3 {
  uvec3 gl_GlobalInvocationID_param;
};

void tint_symbol_1_inner(uvec3 gl_GlobalInvocationID_param) {
  tint_symbol = gl_GlobalInvocationID_param;
  main_1();
}

layout(local_size_x = 1, local_size_y = 1, local_size_z = 1) in;
void tint_symbol_1(tint_symbol_3 tint_symbol_2) {
  tint_symbol_1_inner(tint_symbol_2.gl_GlobalInvocationID_param);
  return;
}
void main() {
  tint_symbol_3 inputs;
  inputs.gl_GlobalInvocationID_param = gl_GlobalInvocationID;
  tint_symbol_1(inputs);
}


Error parsing GLSL shader:
ERROR: 0:50: 'gl_GlobalInvocationID_param' : identifiers starting with "gl_" are reserved 
ERROR: 0:50: '' : compilation terminated 
ERROR: 2 compilation errors.  No code generated.




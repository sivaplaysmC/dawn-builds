#version 310 es
precision mediump float;

uint tint_int_dot(uvec2 a, uvec2 b) {
  return a[0]*b[0] + a[1]*b[1];
}

void dot_97c7ee() {
  uint res = tint_int_dot(uvec2(0u, 0u), uvec2(0u, 0u));
}

struct tint_symbol {
  vec4 value;
};

vec4 vertex_main_inner() {
  dot_97c7ee();
  return vec4(0.0f, 0.0f, 0.0f, 0.0f);
}

tint_symbol vertex_main() {
  vec4 inner_result = vertex_main_inner();
  tint_symbol wrapper_result = tint_symbol(vec4(0.0f, 0.0f, 0.0f, 0.0f));
  wrapper_result.value = inner_result;
  return wrapper_result;
}
void main() {
  tint_symbol outputs;
  outputs = vertex_main();
  gl_Position = outputs.value;
  gl_Position.y = -gl_Position.y;
}


#version 310 es
precision mediump float;

uint tint_int_dot(uvec2 a, uvec2 b) {
  return a[0]*b[0] + a[1]*b[1];
}

void dot_97c7ee() {
  uint res = tint_int_dot(uvec2(0u, 0u), uvec2(0u, 0u));
}

struct tint_symbol {
  vec4 value;
};

void fragment_main() {
  dot_97c7ee();
  return;
}
void main() {
  fragment_main();
}


#version 310 es
precision mediump float;

uint tint_int_dot(uvec2 a, uvec2 b) {
  return a[0]*b[0] + a[1]*b[1];
}

void dot_97c7ee() {
  uint res = tint_int_dot(uvec2(0u, 0u), uvec2(0u, 0u));
}

struct tint_symbol {
  vec4 value;
};

layout(local_size_x = 1, local_size_y = 1, local_size_z = 1) in;
void compute_main() {
  dot_97c7ee();
  return;
}
void main() {
  compute_main();
}



#version 310 es
precision mediump float;


layout (binding = 0) buffer S_1 {
  int i;
} s;

layout(local_size_x = 1, local_size_y = 1, local_size_z = 1) in;
void tint_symbol() {
  return;
}
void main() {
  tint_symbol();
}



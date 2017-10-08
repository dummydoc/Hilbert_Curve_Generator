#version 410

layout(location = 0) in vec2 position;

in float hue;

out float Hue;

void main() {
  gl_Position = vec4(position, 0.0, 1.0);
  Hue = hue;
}

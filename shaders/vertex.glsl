attribute vec3 attr_position;
attribute vec2 attr_uv;

varying vec2 vary_uv;

void main() {
  gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * vec4(attr_position, 1.0);
  vary_uv = attr_uv;
}

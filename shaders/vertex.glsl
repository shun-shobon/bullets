attribute vec3 position;
attribute vec3 color;

varying vec3 vColor;

void main() {
  gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * vec4(position, 1.0);
  vColor = color;
}

varying vec2 vary_uv;
uniform sampler2D unif_texture;

void main() {
    gl_FragColor = texture2D(unif_texture, vary_uv);
}

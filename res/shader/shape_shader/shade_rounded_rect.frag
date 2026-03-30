// frag

uniform float radius;
uniform vec2 halfSize;

float roundedRect(vec2 uv, vec2 h, float r) {
    vec2 q = abs(uv) - h + r;
    return length(max(q, 0.0)) + min(max(q.x, q.y), 0.0) - r;
}


// fragment shader that will create a rounded rect
void main() {
    vec2 uv = gl_TexCoord[0].xy;
    float dist = roundedRect(uv, halfSize, radius);
    float alpha = 1.0 - smoothstep(-1.0, 1.0, dist);
    gl_FragColor = gl_Color * vec4(1.0, 1.0, 1.0, alpha);
}

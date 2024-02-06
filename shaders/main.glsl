

void main()
{
    //getting uv
    vec2 uv = gl_FragCoord.xy / iResolution.xy;
    vec4 col = vec4(uv.x, uv.y, 1.0, 1.0);

    //camera setup

    //camera has literally no depth as it renders a practically 2d game
    
    vec3 pixPos = vec3(uv.x * CamScale.x - CamScale.x / 2, uv.y * CamScale.y - CamScale.y / 2, 0);
    //pixel rotation around camera:
    //pixPos = Rotate3D(pixPos, CamRot);
    pixPos += CamPos;
    col = vec4(pixPos.x, pixPos.y, 0, 1.0);

    gl_FragColor = col;
}
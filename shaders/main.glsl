
//for now not working on actual objects

vec4 RayMarching(vec3 pos)
{
    float finalDist = 10000;
    int hitId = -1;
    for (int i = 0; i < 1; i++)
    {
        float curDist = SingleShape(pos, vec3(0, 0, 0), vec3(0, 0, 0), vec3(1, 1, 1), 1);

        //connecting
        finalDist = min(finalDist, curDist);

        if (finalDist < 0)
        {
        hitId = i;
        }
    }

    //color taking
    if (hitId >= 0)
    {
        return vec4(0.0, 1.0, 1.0, 1.0);
    }
    else //background
    {
        return vec4(1.0, 1.0, 1.0, 1.0);
    }
}


void main()
{
    //getting uv
    vec2 uv = gl_FragCoord.xy / iResolution.xy;
    vec4 col = vec4(uv.x, uv.y, 0.0, 1.0);

    //gl_FragColor = col;
    //return;
    //camera setup

    //camera has literally no depth as it renders a practically 2d game
    
    vec3 pixPos = vec3((uv.x - 0.5) * CamScale.x, (uv.y - 0.5) * CamScale.y, 0);
    //pixel rotation around camera:
    pixPos = Rotate3D(pixPos, CamRot);
    pixPos += CamPos;

    //main program
    col = RayMarching(pixPos);

    //col = vec4(pixPos.x, pixPos.y, 0, 1.0);

    gl_FragColor = col;
}
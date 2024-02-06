float Fill(float dist1, float dist2, float factor)
{

return dist1 + dist2 - factor;
}

float SmoothAdd(float dist1, float dist2, float factor)
{
float h = max(factor - abs(dist1 - dist2), 0) / factor;
return min(dist1, dist2) - h * h * h * factor * 1 / 6.0f;
}
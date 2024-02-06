float Add(float dist1, float dist2)
{
return min(dist1, dist2);
}

float Subtract(float dist1, float dist2)
{
return max(dist1, -dist2);
}

float Intersect(float dist1, float dist2)
{
return max(dist1, dist2);
}
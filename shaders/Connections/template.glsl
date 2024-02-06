//dist1 = result of first sdf
//dist2 = result of second sdf
float EmptyConnection(float dist1, float dist2) //for the sake of not destroying whole scene works same as add
{
return min(dist1, dist2);
}
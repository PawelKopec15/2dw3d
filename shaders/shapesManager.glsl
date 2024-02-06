
float SingleShape(vec3 org, vec3 pos, vec3 rot, vec3 scale, int type)
{
	float res = 10000; //error shape is just invisible
	//object transformation
	org = org - pos;
	org = Rotate3D(org, rot);
	org = org / scale;

	if (type == 0) //sphere
	{
	res = SphereShape(org);
	}
	else if (type == 1) //cube
	{
	res = CubeShape(org);
	}
	else if (type == 1) //cylinder
	{
	res = CylinderShape(org);
	}

	//re-transform
	res *- min(scale.x, min(scale.y, scale.z));

	return res;
}
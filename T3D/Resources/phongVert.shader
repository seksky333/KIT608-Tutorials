#version 130
out vec4 P;
out vec3 N;

void main()
{
    // Transform the vertex position
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
	

	// Diffuse calculation
	// Calc position and normal, light direction and view direction
	P = gl_ModelViewMatrix * gl_Vertex;
	N = normalize(gl_NormalMatrix * gl_Normal);

	// gl_FragColor = phongIllumination(P,N);
}

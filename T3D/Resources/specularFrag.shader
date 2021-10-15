
in vec4 P;
in vec3 N;
float specHighlightsTestThresdhold = 0.5;
vec4 specHighlights(vec4 P, vec3 N)
{
	// Ambient calculation
	vec4 ambient = gl_FrontMaterial.ambient * gl_LightModel.ambient;
	
	// Emission calculation
	vec4 emission = gl_FrontMaterial.emission;

	vec3 L = normalize(gl_LightSource[0].position.xyz - vec3(P * gl_LightSource[0].position.w));
	float diffuseIntensity = max(dot(N, L),0);
	vec4 diffuse = gl_FrontMaterial.diffuse * gl_LightSource[0].diffuse * diffuseIntensity;
	
	// Specular calculation
	vec3 R = normalize(reflect(L,N));
	vec3 V = normalize(P.xyz);

	float specularIntensity = pow(max(dot(R, V),0),2.2*gl_FrontMaterial.shininess);
    //Discrete Specular Highlights
    // if(specularIntensity > gl_FrontMaterial.shininess){
	if(specularIntensity > specHighlightsTestThresdhold){
        specularIntensity = 1.0;
    }else{
        specularIntensity = 0.0;
    }

	vec4 specular = gl_FrontMaterial.specular * gl_LightSource[0].specular * specularIntensity;
	return clamp(ambient+emission+diffuse+specular, 0, 1);
}



void main()
{
    // Do Nothing
    gl_FragColor = specHighlights(P,N);
    // gl_FragColor = diffuseLight(P,N);
}


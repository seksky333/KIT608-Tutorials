
in vec4 P;
in vec3 N;


vec4 diffuseLight(vec4 P, vec3 N)
{
	// Ambient calculation
	vec4 ambient = gl_FrontMaterial.ambient * gl_LightModel.ambient;
	
	// Emission calculation
	vec4 emission = gl_FrontMaterial.emission;

	vec3 L = normalize(gl_LightSource[0].position.xyz - vec3(P * gl_LightSource[0].position.w));
	float diffuseIntensity = max(dot(N, L),0);
	
	//Discrete Diffuse Lighting
	if(diffuseIntensity > ambient.w){
        diffuseIntensity = 1.0;
    }else{
        diffuseIntensity = 0.0;
    }

	vec4 diffuse = gl_FrontMaterial.diffuse * gl_LightSource[0].diffuse * diffuseIntensity;
	
	// Specular calculation
	vec3 R = normalize(reflect(L,N));
	vec3 V = normalize(P.xyz);

	float specularIntensity = pow(max(dot(R, V),0),2.2*gl_FrontMaterial.shininess);

	vec4 specular = gl_FrontMaterial.specular * gl_LightSource[0].specular * specularIntensity;
	
	return clamp(ambient+emission+diffuse+specular, 0, 1);
}


void main()
{
    // Do Nothing
    gl_FragColor = diffuseLight(P,N);
}


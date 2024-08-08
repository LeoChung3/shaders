# version 330 core

out vec4 FragColor;
//in vec3 vertexColour;

in vec3 normals;

uniform vec3 cubeColour;

uniform bool D_light;
uniform bool P_light;
uniform bool S_light;

uniform vec3 lightColour;
uniform vec3 lightDirection;
uniform float ambientFactor;
uniform float shine;
uniform float specStrength;

in vec3 posInWS;

uniform vec3 viewPos;

//point light variables

uniform vec3 plightPosition;
uniform vec3 plightColour;
uniform vec3 pAttentuation;

//spot light variables
uniform vec3 slightPosition;
uniform vec3 slightColour;
uniform vec3 sAttenuation;
uniform vec3 sDirection;
uniform vec2 sRadii;




vec3 n = normalize(normals);
vec3 viewDir = normalize(viewPos - posInWS);
int i = 1;

vec3 getDirectionLight();
vec3 getPointLight(int i);
vec3 getSpotLight();

struct pointLight{
vec3 colour;
vec3 position;
vec3 constants;
};

#define numPL 2
uniform pointLight lights[numPL];

void main(){

	vec3 result;

	if (D_light == true) // if true, adds direction light to result
	{
	result += getDirectionLight();
	}

	if (P_light == true) // if true, adds point light to result
	{
	result += getPointLight(0);
		result += getPointLight(1);


	}

	if (S_light == true) // if true, ads spot light to result
	{
	result += getSpotLight();
	}
	FragColor = vec4(result, 1.0); // RGA

}

vec3 getDirectionLight()
{
	//ambient
	vec3 ambient = cubeColour * lightColour * ambientFactor;

	//diffused
	float diffuseFactor = dot(n, -lightDirection);
	diffuseFactor = max(diffuseFactor, 0.0f);
	vec3 diffuse = cubeColour * lightColour * diffuseFactor;

	//Blinn Phong speculer
	vec3 H = normalize(-lightDirection + viewDir);
	float specLevel = dot(n, H);
	specLevel = max(specLevel, 0.0);
	specLevel = pow(specLevel, shine);
	vec3 specular = lightColour * specLevel * specStrength;


	return ambient + diffuse + specular;
}

vec3 getPointLight(int i)
{
	// attn
	float distance = length(lights[i].position - posInWS);
	float attn = 1.0 / (lights[i].constants.x + (lights[i].constants.y * distance) + (lights[i].constants.z * (distance * distance)));

	vec3 lightDir = normalize((lights[i].position - posInWS));

	//ambient 
	vec3 ambient = cubeColour * lights[i].colour * ambientFactor;

	//diffused
	float diffuseFactor = dot(n, lightDir);
	diffuseFactor = max(diffuseFactor, 0.0f);
	vec3 diffuse = cubeColour * lights[i].colour * diffuseFactor;

	//Blinn Phong speculer
	vec3 H = normalize(lightDir + viewDir);
	float specLevel = dot(n, H);
	specLevel = max(specLevel, 0.0);
	specLevel = pow(specLevel, shine);
	vec3 specular = lights[i].colour * specLevel * specStrength;


	//diffuse
	diffuse = diffuse * attn;
	specular = specular * attn;
	return diffuse + specular + ambient;
}
vec3 getSpotLight()
{
	// attn
	float distance = length(slightPosition - posInWS);
	float attn = 1.0 / (sAttenuation.x + (sAttenuation.y * distance) + (sAttenuation.z * (distance * distance)));

	vec3 lightDir = normalize((slightPosition - posInWS));

	//diffused
	float diffuseFactor = dot(n, lightDir);
	diffuseFactor = max(diffuseFactor, 0.0f);
	vec3 diffuse = cubeColour * slightColour * diffuseFactor;

	//ambient 
	vec3 ambient = cubeColour * slightColour * ambientFactor;


    //specular
	vec3 H = normalize(lightDir + viewDir);
	float specLevel = dot(n, H);
	specLevel = max(specLevel, 0.0);
	specLevel = pow(specLevel, shine);
	vec3 specular = slightColour * specLevel * specStrength;

	diffuse = diffuse * attn;
	specular = specular * attn;


	//spotlight 
	float theta = dot(-lightDir, normalize(sDirection));
	float denom = (sRadii.x - sRadii.y);
	float intensity = (theta - sRadii.y) / denom;
	intensity = clamp(intensity, 0.0, 1.0);

	diffuse = diffuse * intensity;
	specular = specular * intensity;

	return diffuse + specular + ambient;
}

#version 330 core

struct Light 
{
	//vec3 position;
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

uniform Light light;

struct Material 
{
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

uniform Material material;

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal; 

out vec4 FragColor;

uniform vec3 viewPos;



void main()
{
	// Ambient
	vec3 ambient = texture(material.diffuse, TexCoords).rgb * light.ambient;

	// Diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(-light.direction);
	float diff = max(dot(norm, lightDir), 0.0f);
	vec3 diffuse = (diff * texture(material.diffuse, TexCoords).rgb) * light.diffuse;

	// Specular
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
	vec3 specular = (spec * texture(material.specular, TexCoords).rgb) * light.specular;

	vec3 result = ambient + diffuse + specular;
	FragColor = vec4(result, 1.0f);
}
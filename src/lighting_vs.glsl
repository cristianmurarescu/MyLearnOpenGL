#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec3 lightPos;

uniform vec3 objectColor;
uniform vec3 lightColor;

out vec3 FragPos;
out vec3 Normal;

out vec3 result;

out vec3 LightPos;

void main()
{
	FragPos = vec3(view * model * vec4(aPos, 1.0f));
	Normal = mat3(transpose(inverse(view * model))) * aNormal;
	LightPos = vec3(view * vec4(lightPos, 1.0f));
	gl_Position = projection * view * model * vec4(aPos, 1.0);

   	// Ambient
	float ambientStrength = 0.1f;
	vec3 ambient = ambientStrength * lightColor;

	// Diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(LightPos - FragPos);
	float diff = max(dot(norm, lightDir), 0.0f);
	vec3 diffuse = diff * lightColor;

	// Specular
	float specularStrength = 0.5f;
	vec3 viewDir = normalize(-FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 32);
	vec3 specular = specularStrength * spec * lightColor;

	result = (ambient + diffuse + specular) * objectColor;
}

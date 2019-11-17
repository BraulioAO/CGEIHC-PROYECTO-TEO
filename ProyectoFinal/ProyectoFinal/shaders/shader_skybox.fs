#version 330 core

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

out vec4 FragColor;

uniform vec3 ambientColor;
uniform vec3 diffuseColor;
uniform vec3 specularColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;
uniform sampler2D texture1;

void main()
{
    //ambient
    //float ambientStrength = 0.1f;
   // vec3 ambient = ambientStrength * lightColor;

    //diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0f);
    vec3 diffuse = diff * lightColor;

    //Specular
    //float specularStrength = 1.0f;
   // vec3 viewDir = normalize(viewPos - FragPos);
    //vec3 reflectDir = reflect(-lightDir, norm);
    //float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 32);
    // specular = specularStrength * spec * lightColor;

    //Final
   // vec3 result = (ambient * ambientColor) + (diffuse * diffuseColor) + (specular * specularColor);
	vec3 result = (diffuse * diffuseColor) ;
    FragColor = texture(texture1, TexCoords) * vec4(result, 1.0f);
}
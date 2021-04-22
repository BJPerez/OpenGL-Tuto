#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;

uniform vec3 objectColor;
uniform float objectShininess;

uniform vec3 lightColor;
uniform vec3 lightPos;

uniform vec3 viewPos;

uniform float ambientLightStrength;
uniform float specularLightStrength;

void main()
{
    // ambient light
    vec3 ambient = ambientLightStrength * lightColor;

    // diffuse light 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos); 
    float diffuseLightStrength = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diffuseLightStrength * lightColor;

    // specular light
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), objectShininess);
    vec3 specular = specularLightStrength * spec * lightColor;  

    vec3 result = (ambient + diffuse + specular) * objectColor;
    FragColor = vec4(result, 1.0);
}


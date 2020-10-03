#pragma once

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader {
    public:
        Shader();
        Shader(const std::string& vertexPath, const std::string& fragmentPath);

        void use();

        void load(const std::string& vertex, const std::string& fragment);

        void setUniform(const std::string& p_name, int p_value);
        void setUniform(const std::string& p_name, bool p_value);
        void setUniform(const std::string& p_name, float p_value);
        void setUniform(const std::string& p_name, glm::mat4 p_value);
        void setUniform(const std::string& p_name, glm::vec3 p_value);

        unsigned int getId() const;

    private:
        unsigned int m_id;
};
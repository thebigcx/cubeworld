#pragma once

#include <unordered_map>
#include <string>

#include "../shader/Shader.h"
#include "../texture/Texture.h"

template <typename T>
class ResourceHolder
{
    public:
        void add(const std::string& name, const T& resource)
        {
            if (!exists(name))
            {
                m_resources.insert(std::make_pair(name, resource));
            }
            else
            {
                m_resources[name] = resource;
            }
            
        }

        void remove(const std::string& name)
        {
            if (exists(name))
            {
                m_resources.erase(name);
            }
        }

        T& get(const std::string& name)
        {
            if (exists(name))
            {
                return m_resources.at(name);
            }
            
            return m_failResource;
        }

        bool exists(const std::string& name)
        {
            return m_resources.find(name) != m_resources.end();
        }

        void setFailResource(const T& resource)
        {
            m_failResource = resource;
        }

    private:
        std::unordered_map<std::string, T> m_resources;

        T m_failResource;
};
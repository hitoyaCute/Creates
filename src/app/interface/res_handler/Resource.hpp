#pragma once

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <filesystem>
#include <iostream>
#include <string>
#include <unordered_map>


class ResourceManager {
public:
    ResourceManager() = default;

    sf::Font& get_font(const std::string& name, const std::filesystem::path path = "") {
        // check if the font is already loaded
        if (fonts.contains(name)) {
            return fonts.at(name);
        }
        
        // else create new font
        if (!fonts[name].openFromFile(path)) {
            std::cerr << "cant open file at path '" << path << "'" << std::endl;
            exit(-1);
        } else {
            return fonts.at(name);
        }
    }

    sf::Texture& get_texture(const std::string& name, const std::filesystem::path path = "") {
        // check if the font is already loaded
        if (fonts.contains(name)) {
            return textures.at(name);
        }
        
        // else create new font
        if (!textures[name].loadFromFile(path)) {
            std::cerr << "cant open file at path '" << path << "'" << std::endl;
            exit(-1);
        } else {
            return textures.at(name);
        }
    }

    sf::Shader& get_shader(const std::string& name) {
        // check if the font is already loaded
        if (shaders.contains(name)) {
            return shaders.at(name);
        } else {
            std::cerr << "shader named'" << name << "' isnt loaded" << std::endl;
            exit(-1);
        }
    }
    sf::Shader& get_shader(const std::string& name,
                       const std::filesystem::path& filename,
                       const sf::Shader::Type type) {
        // check if the font is already loaded
        if (shaders.contains(name)) {
            return shaders.at(name);
        }

        if (!shaders[name].loadFromFile(filename, type)) {
            std::cerr << "cant open shader '" << "'" << std::endl;
            exit(-1);
        } else {
            return shaders.at(name);
        }
    }
    sf::Shader& get_shader(const std::string& name,
                       const std::filesystem::path& vertexShaderFilename,
                       const std::filesystem::path& fragmentShaderFilename) {
        // check if the font is already loaded
        if (shaders.contains(name)) {
            return shaders.at(name);
        }

        if (!shaders[name].loadFromFile(vertexShaderFilename, fragmentShaderFilename)) {
            std::cerr << "cant open shader '" << "'" << std::endl;
            exit(-1);
        } else {
            return shaders.at(name);
        }
    }   
    sf::Shader& get_shader(const std::string& name,
                           const std::filesystem::path& vertexShaderFilename,
                           const std::filesystem::path& geometryShaderFilename,
                           const std::filesystem::path& fragmentShaderFilename) {
        // check if the font is already loaded
        if (shaders.contains(name)) {
            return shaders.at(name);
        }
        
        if (!shaders[name].loadFromFile(vertexShaderFilename, geometryShaderFilename, fragmentShaderFilename)) {
            std::cerr << "cant open shader '" << "'" << std::endl;
            exit(-1);
        } else {
            return shaders.at(name);
        }
    }
private:
    std::unordered_map<std::string, sf::Font> fonts;
    std::unordered_map<std::string, sf::Shader> shaders;
    std::unordered_map<std::string, sf::Texture> textures;

} static Resources{};






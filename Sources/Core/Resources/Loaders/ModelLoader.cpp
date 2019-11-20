/*
 * Copyright 2018 Vladimir Balun
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "PrecompiledHeader.hpp"
#include "ModelLoader.hpp"

#include <OBJLoader.hpp>

#include "ImageLoader.hpp"
#include "../Model.hpp"
#include "../Image.hpp"
#include "../Material.hpp"
#include "../../Managers/ResourceManager.hpp"

#define UNPACK_OBJ1_VEC2(__vector__) \
    (__vector__).X, (__vector__).Y

#define UNPACK_OBJ1_VEC3(__vector__) \
    (__vector__).X, (__vector__).Y, (__vector__).Z

bool Core::Resources::Loaders::OBJLoader::load(Model& model, const std::string& model_file_path) noexcept
{
    objl::Loader obj_loader{};
    const bool was_loaded = obj_loader.LoadFile(model_file_path);
    if (was_loaded)
    {
        const std::string model_path = model_file_path.substr(0u, model_file_path.find_last_of("\\/") + 1);
        for (const auto& imported_mesh : obj_loader.LoadedMeshes)
        {
            Model::Mesh mesh(imported_mesh.Vertices.size(), imported_mesh.Indices.size());
            for (const auto& imported_vertex : imported_mesh.Vertices)
            {
                glm::vec3 position{ UNPACK_OBJ1_VEC3(imported_vertex.Position) };
                glm::vec3 normal{ UNPACK_OBJ1_VEC3(imported_vertex.Normal) };
                glm::vec2 texture_coordinate{ UNPACK_OBJ1_VEC2(imported_vertex.TextureCoordinate) };
                mesh.emplaceVertex(normal, position, texture_coordinate);
            }
            for (const auto index : imported_mesh.Indices)
            {
                mesh.addIndex(index);
            }

            const std::string mesh_name = imported_mesh.MeshName;
            model.addMesh(mesh_name, std::move(mesh));

            const objl::Material& material = imported_mesh.MeshMaterial;
            if (!material.name.empty())
            {
                loadMaterial(material, model_path);
            }
        }

        return true;
    }

    return false;
}

void Core::Resources::Loaders::OBJLoader::loadMaterial(const objl::Material& material, const std::string& material_path) noexcept
{
    std::string ambient_texture_name = material.map_Ka;
    std::string diffuse_texture_name = material.map_Kd;
    std::string specular_texture_name = material.map_Ks;

    tryLoadImage(ambient_texture_name, material_path);
    tryLoadImage(diffuse_texture_name, material_path);
    tryLoadImage(specular_texture_name, material_path);

    if (!g_resource_manager.isExistsResource<Material>(material.name))
    {
        auto converted_material = std::make_shared<Material>();
        converted_material->setAmbientTextureName(std::move(ambient_texture_name));
        converted_material->setDiffuseTextureName(std::move(diffuse_texture_name));
        converted_material->setSpecularTextureName(std::move(specular_texture_name));
        g_resource_manager.loadResource<Material>(material.name, converted_material);
    }
}

void Core::Resources::Loaders::OBJLoader::tryLoadImage(const std::string& image_filename, const std::string& image_path) noexcept
{
    if (!g_resource_manager.isExistsResource<Image>(image_filename))
    {
        auto image = std::make_shared<Image>();
        const std::string full_filename_path = image_path + image_filename;
        if (ImageLoader::load(*image.get(), full_filename_path))
        {
            g_resource_manager.loadResource<Image>(image_filename, image);
        }
    }
}

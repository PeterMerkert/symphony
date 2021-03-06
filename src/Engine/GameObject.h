#pragma once

#include <vector>
#include "Transform.h"
#include "MeshRenderer.h"

namespace Symphony
{
    class GameObject
    {
    public:
        GameObject();
        GameObject(Transform& t);
        virtual ~GameObject();

        //TO-DO: These two should be abstract
        virtual void Update(float deltaTime);
        virtual void Render(glm::mat4& viewMatrix, glm::mat4& projMatrix);

        inline void SetName(const std::string& newName) { name = newName; }
        inline std::string Name() const { return name; }

        inline void AddChild(GameObject* newChild) 
        {
            if (newChild)
            {
                newChild->parent = this;
                children.push_back(newChild);
            }
        }
        
        inline unsigned int NumberOfChildren() const { return children.size(); }
        inline GameObject* GetChild(unsigned int index) const { return index >= NumberOfChildren() ? nullptr : children[index]; }
        //TO-DO: figure out a way to implement this. Use a unique ID for each GameObject?
        //void RemoveChild(GameObject* c);

        inline void SetPosition(glm::vec3& newPosition) { transform.SetPosition(newPosition); }
        inline glm::vec3 GetPosition() const { return transform.GetPosition(); }

        /*inline void SetScale(glm::vec3& newScale) { transform.scale = newScale; }
        inline glm::vec3 GetScale() const { return transform.scale; }*/
        
        inline MeshRenderer* GetMeshRenderer() const { return meshRenderer; }
        void ModifyMeshRenderer(Mesh* newMesh, Shader* newShader);
        
        //TO-DO: Should attributes like the parent be public?
        inline GameObject* GetParent() const { return parent; }
        inline void SetParent(GameObject* newParent) { parent = newParent; }

        inline Transform* GetTransform() { return &transform; }

    protected:
        std::string name;
        GameObject* parent;
        Transform transform;
        MeshRenderer* meshRenderer;
        std::vector<GameObject*> children;

        bool isEnabled;
    };
}
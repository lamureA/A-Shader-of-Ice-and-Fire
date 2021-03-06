#include "mesh.hh"

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, std::vector<Texture>& textures, GLuint draw_mode)
{
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;
    this->draw_mode = draw_mode;

    setup_mesh();
}

void Mesh::setup_mesh()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    // vertex positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tex_coords));
    // vertex tangent
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tangent));
    // vertex bitangent
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, bitangent));

    glBindVertexArray(0);
}

void Mesh::draw(Program& program, std::vector<GLuint>* other_textures)
{
    unsigned int diffuse_n = 1;
    unsigned int specular_n = 1;
    unsigned int normal_n = 1;
    for(unsigned int i = 0; i < textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i); // activate proper texture unit before binding
        // retrieve texture number (the N in diffuse_textureN)
        std::string number;
        std::string name = textures[i].type;
        if(name == "texture_diffuse")
            number = std::to_string(diffuse_n++);
        else if(name == "texture_specular")
            number = std::to_string(specular_n++);
        else if(name == "texture_normal")
            number = std::to_string(normal_n++);
        program.set_int(name + number, i);
        //std::cout << "Texture " << name + number << ": " << i << " has id " << textures[i].id  << " and path " << textures[i].path << std::endl;
        glBindTexture(GL_TEXTURE_2D, textures[i].id);
    }

    if (other_textures)
    {
        for (unsigned int i = 0; i < other_textures->size(); ++i)
        {
            unsigned int index = i + textures.size();
            glActiveTexture(GL_TEXTURE0 + index);
            glBindTexture(GL_TEXTURE_2D, (*other_textures)[i]);
            program.set_int("texture_other" + std::to_string(i), index);
            //std::cout << "Texture_other " << i << ": " << index << std::endl;
        }
    }

    glActiveTexture(GL_TEXTURE0);

    // draw mesh
    glBindVertexArray(VAO);
    glDrawElements(draw_mode, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
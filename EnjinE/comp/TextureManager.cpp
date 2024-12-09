#include "TextureManager.h"
#include "utils/Utils.h"

TextureManager::TextureManager() {
}

sf::Texture* TextureManager::getTexture(std::wstring name)
{
    if (m_textures.find(name) != m_textures.end()) {
        return m_textures[name];
    }
    else {
        return NULL;
    }
}
size_t TextureManager::getIDbyName(std::wstring name) {
    size_t id = no_texture_id;

    auto it = std::find(m_order.begin(), m_order.end(), name);

    if ( it != m_order.end() ) {
        id = std::distance(m_order.begin(), it);
    }

    return id;
}
std::wstring TextureManager::getNamebyID(size_t id)
{
    std::wstring name = L"no_texture";

    if (id < m_order.size()) name = m_order[id];

    return name;
}
sf::Texture* TextureManager::getTexture(int index)
{
    if (m_order.size() == index || index > m_order.size()) return nullptr;
    std::wstring name = m_order.at(index);
    return getTexture(name);
}

void TextureManager::loadTexturesFromRootResources(fs::path dir)
{
    fs::path dirtoremove = fs::current_path() / L"Resources\\Textures";

    struct _stat sb;

    fs::path path = fs::path(dir);
    for (const auto& entry : fs::directory_iterator(path.string().c_str())) {
        fs::path outfilename = entry.path();
        std::wstring outfilename_str = outfilename.wstring();
        const wchar_t* path = outfilename_str.c_str();

        if (_wstat(path, &sb) == 0 && !(sb.st_mode & S_IFDIR)) {
            outfilename_str.erase(0, dirtoremove.wstring().size() + 1);

            outfilename_str.erase(outfilename_str.end() - 4, outfilename_str.end());

            outfilename_str = Utils::string::replace(outfilename_str, '\\', '_');

            sf::Texture* texture = new sf::Texture();
            
            if (texture->loadFromFile(entry.path().string()))
            {
                texture->setRepeated(false);
                texture->setSmooth(false);
                m_textures[outfilename_str] = texture;
                m_order.push_back(outfilename_str);
                if (outfilename_str == L"no_texture") no_texture_id = m_order.size();
            }
            else
            {
                //std::format(L"[-] Загрузка тестуры {}", outfilename_str).c_str()
                delete texture;
                continue;
            }
        }
        else {
            loadTexturesFromRootResources(path);
        }
    }
    //getGame()->getLogger()->info(std::format(L"Загружено {} текстур", m_order.size()).c_str());
}


#include "Engine.h"

// MOVE TO UTILS.CPP
template<typename TK, typename TV>
std::vector<TV> extractValues(std::map<TK, TV> const& input_map) {
    std::vector<TV> retval;
    for (auto const& element : input_map) {
        retval.push_back(element.second);
    }
    return retval;
}
// MOVE TO UTILS.CPP
template<typename TK, typename TV>
std::vector<TK> extractKeys(std::map<TK, TV> const& input_map) {
    std::vector<TK> retval;
    for (auto const& element : input_map) {
        retval.push_back(element.first);
    }
    return retval;
}


Engine::Engine() {

}

void Engine::update(RendererManager RM, PhysicsWorld PW) {
    std::vector<std::string> physicsBodies = extractKeys(this->m_associations);
    std::vector<std::string> models = extractValues(this->m_associations);

    for (int i = 0; i < physicsBodies.size(); i++) {
        RM.model(models[i])->position(PW.physicsBody(physicsBodies[i])->position());
    }
}

void Engine::link(std::string pb, std::string m) {
    this->m_associations[pb] = m;
}
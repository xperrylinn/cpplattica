#include "simulation_result.h"
#include "mpi_state_change.h"


SimulationResult::SimulationResult() {}

SimulationResult::SimulationResult(SimulationState initial_state) {
    // std::cout << "SimulationResult(SimulationState initial_state)" << std::endl;
    this->initial_state = initial_state;
    this->_diffs = {};
}

void SimulationResult::add_step(std::vector<mpi_state_change> state_change) {
    // std::cout << "SimulationResult::add_step(std::unordered_map<int, int> state)" << std::endl;
    this->_diffs.push_back(state_change);
}

void SimulationResult::set_output(SimulationState step) {
    // std::cout << "SimulationResult::set_output(SimulationState step)" << std::endl;
    this->output = step;
}

const std::vector<std::vector<mpi_state_change>> SimulationResult::get_diffs() const {
    // std::cout << "SimulationResult::get_diffs()" << std::endl;
    return this->_diffs;
}

void SimulationResult::set_diffs(std::vector<std::vector<mpi_state_change>> diffs) {
    this->_diffs = diffs;
}

const std::string SimulationResult::to_json() const {
    // std::cout << "PeriodicStructure::to_json()" << std::endl;
    // return {
    //     "initial_state": self.initial_state.as_dict(),
    //     "diffs": self._diffs,
    //     "@module": self.__class__.__module__,
    //     "@class": self.__class__.__name__,
    // }  

    std::ostringstream oss;
    oss << "[";
    bool first_outer = true;
    
    for (const auto& rank_changes : this->_diffs) {
        if (!first_outer) {
            oss << ",";
        }
        oss << "{ \"SITES\": {";
        bool first_inner = true;
        
        for (const auto& change : rank_changes) {
            if (!first_inner) {
                oss << ",";
            }
            oss << "\"" << change.site_id << "\": { \"STATE\": " 
                << change.new_state << "}";
            first_inner = false;
        }
        
        oss << "}, \"GENERAL\": {} }";
        first_outer = false;
    }
    
    oss << "]";

    std::ostringstream result;
    result << "{\"initial_state\": " << this->initial_state.to_json();
    result << ", \"diffs\": " << oss.str();
    result << ", \"@module\": " <<  "\"pylattica.core.simulation_result\"";
    result << ", \"@class\": " <<  "\"SimulationResult\"";
    result << "}";
    return result.str();
}
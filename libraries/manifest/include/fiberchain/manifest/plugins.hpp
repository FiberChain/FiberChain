
#pragma once

#include <memory>
#include <string>
#include <vector>

namespace fiberchain { namespace app {

class abstract_plugin;
class application;

} }

namespace fiberchain { namespace plugin {

void initialize_plugin_factories();
std::shared_ptr< fiberchain::app::abstract_plugin > create_plugin( const std::string& name, fiberchain::app::application* app );
std::vector< std::string > get_available_plugins();

} }

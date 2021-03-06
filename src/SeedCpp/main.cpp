#include "Core.h"

#include "../DbSQLiteAdapter/Connection.h"
#include "../DbSQLiteAdapter/ConnectionConfiguration.h"

#include "../RapidJSONAdapter/JSONAdapter.h"

#include "../WebServer/WebServer.h"
#include "../WebServerInterface/Model/CORSConfiguration.h"
#include "../WebServerInterface/Model/Configuration.h"

int main() {
  try {
    // Database
    systelab::db::sqlite::ConnectionConfiguration databaseConfiguration(
        "./seed_cpp.db");
    systelab::db::sqlite::Connection databaseConnection;
    std::unique_ptr<systelab::db::IDatabase> database =
        databaseConnection.loadDatabase(databaseConfiguration);

    // Web server
    std::string hostAddress = "127.0.0.1";
    unsigned int port = 8080;
    unsigned int threadPoolSize = 5;
    systelab::web_server::Configuration webServerConfiguration(
        hostAddress, port, threadPoolSize);

    systelab::web_server::CORSConfiguration &corsConfiguration =
        webServerConfiguration.getCORSConfiguration();
    corsConfiguration.setEnabled(true);
    corsConfiguration.addAllowedOrigin("*");
    corsConfiguration.setAllowedHeaders(
        "origin, content-type, accept, authorization, Etag, if-none-match");
    corsConfiguration.setAllowedCredentials(true);
    corsConfiguration.setAllowedMethods(
        "GET, POST, PUT, DELETE, OPTIONS, HEAD");
    corsConfiguration.setMaxAge(1209600);
    corsConfiguration.setExposedHeaders(
        "origin, content-type, accept, authorization, ETag, if-none-match");

    std::unique_ptr<systelab::web_server::IWebServer> webServer(
        new systelab::web_server::WebServer(webServerConfiguration));

    // JSON adapter
    std::unique_ptr<systelab::json_adapter::IJSONAdapter> jsonAdapter =
        std::make_unique<
            systelab::json_adapter::rapidjson_adapter::JSONAdapter>();

    // Seed Core
    seed_cpp::Core core(std::move(database), std::move(webServer),
                        std::move(jsonAdapter));
    core.execute();

    std::cout << "Seed core is now running..." << std::endl;
    while (true) {
    }
  } catch (std::exception &e) {
    std::cout << "Unable to start seed core:" << std::endl << e.what();
  }

  return 0;
}

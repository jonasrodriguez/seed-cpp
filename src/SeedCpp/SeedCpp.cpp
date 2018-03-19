#include "stdafx.h"
#include "SeedCppCore/Core.h"

#include "DbSQLiteAdapter/Connection.h"
#include "DbSQLiteAdapter/ConnectionConfiguration.h"

#include "WebServer/WebServer.h"
#include "WebServerInterface/Model/Configuration.h"



int main()
{
	systelab::db::sqlite::ConnectionConfiguration databaseConfiguration("./database.db");
	systelab::db::sqlite::Connection databaseConnection;
	std::unique_ptr<systelab::db::IDatabase> database = databaseConnection.loadDatabase(databaseConfiguration);

	std::string hostAddress = "127.0.0.1";
	unsigned int port = 8080;
	unsigned int threadPoolSize = 5;
	systelab::web_server::Configuration webServerConfiguration(hostAddress, port, threadPoolSize);
	std::unique_ptr<systelab::web_server::IWebServer> webServer(new systelab::web_server::WebServer(webServerConfiguration));

	seed_cpp::Core core(std::move(database), std::move(webServer));
	core.execute();

	return 0;
}


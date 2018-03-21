#include "StdAfx.h"
#include "Core.h"

#include "DAL/DAO/Db/DbDAOFactory.h"
#include "DAL/Translators/Db/DbTranslatorsFactory.h"
#include "Model/Model.h"

#include "DbAdapterInterface/IDatabase.h"

#include "WebServerInterface/IWebServer.h"


namespace seed_cpp {

	Core::Core(std::unique_ptr<systelab::db::IDatabase> database,
			   std::unique_ptr<systelab::web_server::IWebServer> webServer)
		:m_database(std::move(database))
		,m_webServer(std::move(webServer))
	{
		m_model.reset(new model::Model());
		m_dbTranslatorsFactory.reset(new dal::DbTranslatorsFactory());
		m_dbDAOFactory.reset(new dal::DbDAOFactory(*this));
	}

	Core::~Core()
	{
	}

	void Core::execute()
	{
		m_webServer->start();
	}

	systelab::db::IDatabase& Core::getDatabase() const
	{
		return *m_database;
	}

	systelab::web_server::IWebServer& Core::getWebServer() const
	{
		return *m_webServer;
	}

	model::Model& Core::getModel() const
	{
		return *m_model;
	}

	dal::IDbTranslatorsFactory& Core::getDbTranslatorsFactory() const
	{
		return *m_dbTranslatorsFactory;
	}

	dal::IDbDAOFactory& Core::getDbDAOFactory() const
	{
		return *m_dbDAOFactory;
	}

}

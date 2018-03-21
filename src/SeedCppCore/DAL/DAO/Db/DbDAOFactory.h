#pragma once

#include "DAL/DAO/ITransactionDAOMgr.h"
#include "DAL/DAO/Db/IDbDAOFactory.h"


namespace seed_cpp
{
	class Core;
}

namespace seed_cpp { namespace dal {

	class DbDAOFactory : public IDbDAOFactory
					   , public ITransactionDAOMgr
	{
	public:
		DbDAOFactory(Core& core);
		virtual ~DbDAOFactory();

		std::unique_ptr<ILoadDAO> buildPatientLoadDAO(model::EntityMgr<model::Patient>&);
		std::unique_ptr<ISaveDAO> buildPatientSaveDAO(model::Patient&);

		std::unique_ptr<ITransactionDAO> startTransaction();

		void releaseTransactionInProgress();

	protected:
		Core& m_core;
		bool m_transactionInProgress;
	};

}}
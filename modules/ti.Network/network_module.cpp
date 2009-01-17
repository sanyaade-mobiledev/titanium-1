/**
 * Appcelerator Titanium - licensed under the Apache Public License 2
 * see LICENSE in the root folder for details on the license.
 * Copyright (c) 2008 Appcelerator, Inc. All Rights Reserved.
 */
#include "network_module.h"
#include "network_binding.h"

using namespace kroll;
using namespace ti;


namespace ti
{
	KROLL_MODULE(NetworkModule);

	void NetworkModule::Initialize()
	{
		// load our variables
		this->variables = new NetworkBinding(host->GetGlobalObject());

		// set our ti.Network
		Value *value = new Value(this->variables);
		host->GetGlobalObject()->Set("Network",value);
	}

	void NetworkModule::Destroy()
	{
		KR_DECREF(this->variables);
	}
}

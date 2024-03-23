#include "fabryka2.h"
#include "IKlasa2.h"
#include <new>
#include "Klasa2.h"


extern volatile ULONG numberOfUsedInstances;


fabryka2::fabryka2()
{
	m_ref = 0;
	numberOfUsedInstances++;
}


fabryka2::~fabryka2()
{
	numberOfUsedInstances--;
}

HRESULT fabryka2::QueryInterface(REFIID InterfaceIdentifier, void ** InterfacePointer)
{
	if (InterfacePointer == NULL) return E_POINTER;
	*InterfacePointer = NULL;
	if (InterfaceIdentifier == IID_IUnknown || InterfaceIdentifier == IID_IClassFactory) *InterfacePointer = this;
	if (*InterfacePointer != NULL) {
		AddRef();
		return S_OK;
	};
	return E_NOINTERFACE;
}

ULONG fabryka2::AddRef()
{
	/*
	Tutaj zaimplementuj dodawanie referencji na obiekt.
	 */
}

ULONG fabryka2::Release()
{
	/*
	Tutaj zaimplementuj usuwania referencji na obiekt.
	Jeżeli nie istnieje żadna referencja obiekt powinien zostać usunięty.
	 */
}

HRESULT fabryka2::LockServer(BOOL blocked)
{
	if (blocked) numberOfUsedInstances++;
	else numberOfUsedInstances--;

	return S_OK;
}

HRESULT fabryka2::CreateInstance(IUnknown * outerInterface, REFIID InterfaceIdentifier, void ** InterfacePointer)
{
	if (InterfacePointer == NULL) return E_POINTER;
	*InterfacePointer = NULL;
	if (InterfaceIdentifier != IID_IUnknown && InterfaceIdentifier != IID_IKlasa2) return E_NOINTERFACE;

	Klasa2 *obj = new (std::nothrow) Klasa2();
	if (obj == NULL)
		return E_OUTOFMEMORY;

	HRESULT rv = obj->QueryInterface(InterfaceIdentifier, InterfacePointer);
	if (FAILED(rv))
	{
		delete obj;
		*InterfacePointer = NULL;
	};
	return rv;

}

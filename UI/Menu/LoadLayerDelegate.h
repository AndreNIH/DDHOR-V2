#pragma once
#include <memory>

class LoaderDelegate {
private:
	typedef void(__thiscall* opSMH)(void*, void*);
	void* m_layerDelegate = nullptr;
	opSMH m_methodDelegate = nullptr;
public:
	LoaderDelegate(void* sender, uint32_t method) {
		m_layerDelegate = sender;
		m_methodDelegate = reinterpret_cast<opSMH>(method);
	}

	void invokeLoader() {
		if (m_methodDelegate && m_layerDelegate)
			m_methodDelegate(m_layerDelegate, nullptr);
	};
};

class LoaderProtocol {
protected:
	std::shared_ptr<LoaderDelegate>m_delegate;
public:
	void setNewLoaderContext(void* sender, uint32_t method) {
		m_delegate = std::make_unique<LoaderDelegate>(sender, method);
	}

	void setLoaderContext(std::shared_ptr<LoaderDelegate> ptr) {
		m_delegate = ptr;
	}

	std::shared_ptr<LoaderDelegate> getLoaderContext() {
		return m_delegate;
	}
};

#include <QCoreApplication>
#include <common/mvc/View.h>
#include <common/model/Parameter.h>
#include <cfloat>
#include <cmath>
#include <memory>

using namespace de::bswalz::mvc;
using namespace de::bswalz::model;

class ModelTest : public de::bswalz::mvc::View {
public:
	ModelTest();
	virtual ~ModelTest() {}
	void    test();
	virtual void update(const Model *, void* ) override;
private:
	std::unique_ptr<CUShortParameter> m_pUShortParameter;
	std::unique_ptr<CUIntParameter> m_pUIntParameter;
	std::unique_ptr<CULongParameter> m_pULongParameter;
	std::unique_ptr<CULongLongParameter> m_pULonglongParameter;
	std::unique_ptr<CShortParameter> m_pShortParameter;
	std::unique_ptr<CIntParameter> m_pIntParameter;
	std::unique_ptr<CLongParameter> m_pLongParameter;
	std::unique_ptr<CLongLongParameter> m_pLonglongParameter;
	std::unique_ptr<CFloatParameter> m_pFloatParameter;
	std::unique_ptr<CDoubleParameter> m_pDoubleParameter;
	std::unique_ptr<CBoolParameter> m_pBoolParameter;

	std::unique_ptr<TAssignRule<unsigned short>> m_pUShortAssignRule;
	std::shared_ptr<TVoter<unsigned int>>        m_pUIntVoter;
};

ModelTest::ModelTest() {
	m_pUShortParameter.reset( new CUShortParameter("USHORT", 0, 0, 0x7F) );
	m_pUIntParameter.reset( new CUIntParameter("UINT", 0, 0, INT_MAX) );
	m_pULongParameter.reset( new CULongParameter("ULONG", 0, 0, LONG_MAX) );
	m_pULonglongParameter.reset( new CULongLongParameter("ULONGLONG", 0, 0, LONG_MAX) );
	m_pShortParameter.reset( new CShortParameter("SHORT", 0, -0x7F, 0x7F) );
	m_pIntParameter.reset( new CIntParameter("INT", 0, INT_MIN, INT_MAX) );
	m_pLongParameter.reset( new CLongParameter("LONG", 0, LONG_MIN, LONG_MAX) );
	m_pLonglongParameter.reset( new CLongLongParameter("LONGLONG", 0, LONG_LONG_MIN, LONG_LONG_MAX) );
	m_pFloatParameter.reset( new CFloatParameter("FLOAT", 0.0f, -FLT_MAX, FLT_MAX) );
	m_pDoubleParameter.reset( new CDoubleParameter("DOUBLE", 0.0f, -DBL_MAX, DBL_MAX) );
	m_pBoolParameter.reset( new CBoolParameter("BOOL", false) );

	// Application of AssignRule
	// Here: Value of m_pUShortParameter -> m_pUIntParameter
	class MyAssignRule : public TAssignRule<unsigned short> {
	public:
		MyAssignRule(CUIntParameter * pDestParameter)
			: TAssignRule<unsigned short>(), m_pDestParameter(pDestParameter) {}
		virtual ~MyAssignRule() {}
		virtual void apply(TModel<unsigned short> * pSource) override {
							unsigned short v = dynamic_cast<CUShortParameter*>(pSource)->getValue();
							m_pDestParameter->assignValue(v, this);
							};
		virtual void revert() override {
							m_pDestParameter->revertAssignment();
							};
		virtual bool validate() override {
							return m_pDestParameter->getVoter()->vote();
							};
	private:
		CUIntParameter * m_pDestParameter;
	}; // End class MyAssignRule
	m_pUShortAssignRule.reset( new MyAssignRule(m_pUIntParameter.get()) );
	m_pUShortParameter->addAssignRule(m_pUShortAssignRule.get());

	// Application of Voter
	// Here: Voter does not accept values < 1000
	class MyVoter : public TVoter<unsigned int> {
	public:
		MyVoter(CUIntParameter * pParameter)
			: TVoter<unsigned int>(), m_pDestParameter(pParameter) {}
		virtual ~MyVoter() {}
		virtual bool vote() override {
							unsigned int v = m_pDestParameter->getValue();
							return v >= 1000;
							};
	private:
		CUIntParameter * m_pDestParameter;
	}; // End class MyVoter
	m_pUIntVoter.reset( new MyVoter(m_pUIntParameter.get()) );
	m_pUIntParameter->setVoter(m_pUIntVoter);

	registerAt(m_pUShortParameter.get());
	registerAt(m_pUIntParameter.get());
	registerAt(m_pULongParameter.get());
	registerAt(m_pULonglongParameter.get());
	registerAt(m_pShortParameter.get());
	registerAt(m_pIntParameter.get());
	registerAt(m_pLongParameter.get());
	registerAt(m_pLonglongParameter.get());
	registerAt(m_pFloatParameter.get());
	registerAt(m_pDoubleParameter.get());
	registerAt(m_pBoolParameter.get());
}

void ModelTest::test() {
	m_pUShortParameter->assignValue(123);
	m_pUIntParameter->assignValue(1234);
	m_pULongParameter->assignValue(12345);
	m_pULonglongParameter->assignValue(123456);
	m_pShortParameter->assignValue(-123);
	m_pIntParameter->assignValue(-1234);
	m_pLongParameter->assignValue(-12345);
	m_pLonglongParameter->assignValue(-123456);
	m_pFloatParameter->assignValue(M_PI);
	m_pDoubleParameter->assignValue(M_PI);
	m_pBoolParameter->assignValue(true);
}

void ModelTest::update(const Model * pModel, void* pObj) {
	std::string s;
	if (dynamic_cast<const CUShortParameter*>(pModel) != nullptr)
		s = dynamic_cast<const CUShortParameter*>(pModel)->getValueAsString();
	else if (dynamic_cast<const CUIntParameter*>(pModel) != nullptr)
		s = dynamic_cast<const CUIntParameter*>(pModel)->getValueAsString();
	else if (dynamic_cast<const CULongParameter*>(pModel) != nullptr)
		s = dynamic_cast<const CULongParameter*>(pModel)->getValueAsString();
	else if (dynamic_cast<const CULongLongParameter*>(pModel) != nullptr)
		s = dynamic_cast<const CULongLongParameter*>(pModel)->getValueAsString();
	else if (dynamic_cast<const CShortParameter*>(pModel) != nullptr)
		s = dynamic_cast<const CShortParameter*>(pModel)->getValueAsString();
	else if (dynamic_cast<const CIntParameter*>(pModel) != nullptr)
		s = dynamic_cast<const CIntParameter*>(pModel)->getValueAsString();
	else if (dynamic_cast<const CLongParameter*>(pModel) != nullptr)
		s = dynamic_cast<const CLongParameter*>(pModel)->getValueAsString();
	else if (dynamic_cast<const CLongLongParameter*>(pModel) != nullptr)
		s = dynamic_cast<const CLongLongParameter*>(pModel)->getValueAsString();
	else if (dynamic_cast<const CFloatParameter*>(pModel) != nullptr)
		s = dynamic_cast<const CFloatParameter*>(pModel)->getValueAsString();
	else if (dynamic_cast<const CDoubleParameter*>(pModel) != nullptr)
		s = dynamic_cast<const CDoubleParameter*>(pModel)->getValueAsString();
	else if (dynamic_cast<const CBoolParameter*>(pModel) != nullptr)
		s = ((CBoolParameter*)pModel)->getValue() ? "true" : "false";
	if (!s.empty())
		qDebug((pModel->getName() + std::string(" : ") + s).c_str());
}

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	ModelTest modeltest;
	modeltest.test();

	return a.exec();
}

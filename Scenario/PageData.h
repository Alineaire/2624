#ifndef PAGEDATA_H
#define PAGEDATA_H

#include "DescriptorData.h"
#include "LinkData.h"

#include <vector>
#include <string>

using namespace std;

class PageData
{
    public:
        PageData();
        PageData(string _name);
        virtual ~PageData();
        void read();
        void unload();
        void update();
        void parse(const char** _headerFields, const char** _rowFields, int _nbRows);

        string m_name;
        vector<IDescriptorData*> m_descriptors;
        vector<LinkData*> m_links;

    protected:
    private:
};

#endif // PAGEDATA_H

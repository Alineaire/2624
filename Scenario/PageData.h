#ifndef PAGEDATA_H
#define PAGEDATA_H

#include "DescriptorData.h"
#include "LinkData.h"

#include <list>

using namespace std;

class PageData
{
    public:
        PageData();
        virtual ~PageData();
        void read();
        void unload();
        void update();

        list<IDescriptorData> m_descriptors;
        list<LinkData> m_links;

    protected:
    private:
};

#endif // PAGEDATA_H

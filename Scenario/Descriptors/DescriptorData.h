#ifndef DESCRIPTORDATA_H
#define DESCRIPTORDATA_H

#include "TagData.h"

#include <string>

using namespace std;

class IDescriptorData
{
    public:
        IDescriptorData();
        virtual ~IDescriptorData();
        virtual void read() {}
        virtual void unload() {}

    protected:
    private:
};

class BoolTagModifierDescriptorData : public IDescriptorData
{
    public:
        BoolTagModifierDescriptorData();
        virtual ~BoolTagModifierDescriptorData();

        BoolTagData* m_data;
        ChangeBool m_action;

    protected:
    private:
};

class IntTagModifierDescriptorData : public IDescriptorData
{
    public:
        IntTagModifierDescriptorData();
        virtual ~IntTagModifierDescriptorData();

        IntTagData* m_data;
        int m_toAdd = 1;

    protected:
    private:
};

class SoundDescriptorData : public IDescriptorData
{
    public:
        SoundDescriptorData();
        virtual ~SoundDescriptorData();
        void read();
        void unload();

        string m_sound;

    protected:
    private:
};

class MusicDescriptorData : public IDescriptorData
{
    public:
        MusicDescriptorData();
        virtual ~MusicDescriptorData();
        void read();
        void unload();

        string m_sound;

    protected:
    private:
};

class TextDescriptorData : public IDescriptorData
{
    public:
        TextDescriptorData();
        virtual ~TextDescriptorData();
        void read();

        string m_text;

    protected:
    private:
};

class ImageDescriptorData : public IDescriptorData
{
    public:
        ImageDescriptorData();
        virtual ~ImageDescriptorData();
        void read();
        void unload();

        string m_sprite;

    protected:
    private:
};

#endif // DESCRIPTORDATA_H

#ifndef DESCRIPTORDATA_H
#define DESCRIPTORDATA_H

#include "TagData.h"
#include "Text.h"

#include <string>
#include <vector>

using namespace std;

class IDescriptorData
{
    public:
        IDescriptorData();
        virtual ~IDescriptorData() {}
        virtual void read() {}
        virtual void unload() {}
        virtual void update() {}

    protected:
    private:
};

class BoolTagModifierDescriptorData : public IDescriptorData
{
    public:
        BoolTagModifierDescriptorData() {}
        virtual ~BoolTagModifierDescriptorData() {}
        void read();
        static void parse(vector<IDescriptorData*>& _descriptors, string _text);

        BoolTagData* m_data;
        ChangeBool m_action;
        bool m_value;

    protected:
    private:
};
class IntTagModifierDescriptorData : public IDescriptorData
{
    public:
        IntTagModifierDescriptorData() {}
        virtual ~IntTagModifierDescriptorData() {}
        void read();
        static void parse(vector<IDescriptorData*>& _descriptors, string _text);

        IntTagData* m_data;
        ChangeInt m_action;
        int m_value;

    protected:
    private:
};
class StringTagModifierDescriptorData : public IDescriptorData
{
    public:
        StringTagModifierDescriptorData() {}
        virtual ~StringTagModifierDescriptorData() {}
        void read();
        static void parse(vector<IDescriptorData*>& _descriptors, string _text);

        StringTagData* m_data;
        ChangeString m_action;
        string m_value;

    protected:
    private:
};

class SFXDescriptorData : public IDescriptorData
{
    public:
        SFXDescriptorData() {}
        virtual ~SFXDescriptorData() {}
        void read();
        void unload();
        static void parse(vector<IDescriptorData*>& _descriptors, string _text);

        string m_sound;

    protected:
    private:
};

class MusicDescriptorData : public IDescriptorData
{
    public:
        MusicDescriptorData() {}
        virtual ~MusicDescriptorData() {}
        void read();
        void unload();
        static void parse(vector<IDescriptorData*>& _descriptors, string _text);

        string m_sound;

    protected:
    private:
};

class TextDescriptorData : public IDescriptorData
{
    public:
        TextDescriptorData() {}
        virtual ~TextDescriptorData() {}
        void read();
        void unload();
        void update();
        static void parse(vector<IDescriptorData*>& _descriptors, string _idText);

        Text m_text;

    protected:
    private:
};

class SpriteDescriptorData : public IDescriptorData
{
    public:
        SpriteDescriptorData() {}
        virtual ~SpriteDescriptorData() {}
        void read();
        void unload();
        static void parse(vector<IDescriptorData*>& _descriptors, string _text);

        string m_sprite;

    protected:
    private:
};

class ColorDescriptorData : public IDescriptorData
{
    public:
        ColorDescriptorData() {}
        virtual ~ColorDescriptorData() {}
        void read();
        static void parse(vector<IDescriptorData*>& _descriptors, string _text);

        int m_red;
        int m_green;
        int m_blue;

    protected:
    private:
};

class BrightnessDescriptorData : public IDescriptorData
{
    public:
        BrightnessDescriptorData() {}
        virtual ~BrightnessDescriptorData() {}
        void read();
        static void parse(vector<IDescriptorData*>& _descriptors, string _text);

        int m_brightness;

    protected:
    private:
};

class ArduinoDescriptorData : public IDescriptorData
{
    public:
        ArduinoDescriptorData() {}
        virtual ~ArduinoDescriptorData() {}
        void read();
        static void parse(vector<IDescriptorData*>& _descriptors, string _text);

        string m_text;

    protected:
    private:
};

#endif // DESCRIPTORDATA_H

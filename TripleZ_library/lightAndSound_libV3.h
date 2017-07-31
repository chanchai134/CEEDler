#define Light_port 3
#define Sound_port 6
#define TV_port 11
#define SOUND_DOWN 10
int brightness = 0;
int soundlevel = 0;
int keep = -1;
int level_update_now;
boolean check_update = false;
void lightAndSound_strat()
{
	pinMode(Light_port,OUTPUT);
    pinMode(Sound_port,OUTPUT);
    pinMode(TV_port,OUTPUT);
}
//////////////////////////////////////////////////////////
void lightAndSound_on(int max_setting,String Object)
{
    if(Object == "light")
    {
        analogWrite(Light_port,max_setting);
        brightness = max_setting;
    }
    else
    {
        analogWrite(Sound_port,(int)(max_setting/SOUND_DOWN));
        analogWrite(TV_port,max_setting);
        soundlevel = max_setting;
    }
}
void lightAndSound_off(String Object)
{
    if(Object == "light")
    {
        analogWrite(Light_port,0);
        brightness = 0;
    }
    else
    {
        analogWrite(Sound_port,0);
        analogWrite(TV_port,0);
        soundlevel = 0;
    }
}
//////////////////////////////////////////////////////////
void check_do_function_light()
{
    level_update_now = tripleZ_network_readtext("ceedlerOutRangeLight").toInt();
    if(keep != level_update_now && keep != -1)
    {
        lightAndSound_on(level_update_now,"light");
        check_update = true;
    }
}
void check_do_function_sound()
{
    level_update_now = tripleZ_network_readtext("ceedlerOutRangeLight").toInt();
    if(keep != level_update_now && keep != -1)
    {
        lightAndSound_on(level_update_now,"TV");
        check_update = true;
    }
}
///////////////////////////////////////////////////////////
void lightAndSound_increase(int time,int max,String Object)
{
    if(Object == "light")
    {
        keep = tripleZ_network_readtext("ceedlerOutRangeLight").toInt();
    }
    else
    {
        keep = tripleZ_network_readtext("ceedlerOutTV").toInt();
    }
    int delay_time_light = (time*1000)/(max-brightness);
    int delay_time_sound = (time*1000)/(max-soundlevel);
    int count_time_function;
    if(Object == "light")
    {
        count_time_function = 1000/delay_time_light;
    }
    else
    {
        count_time_function = 1000/delay_time_sound;
    } 
    int count_function = 0;
    if(Object == "light")
    {
        while(brightness < max)
        {
            brightness++;
            analogWrite(Light_port,brightness);
            delay(delay_time_light);
            //////////////////////////////////////////
            count_function += count_time_function;
            if(count_function > 1000)
            {
                //do sth
                check_do_function_light();
                delay(50);
                keep = -1;
                count_function = 0;
                if(check_update)
                {
                    check_update = !check_update;
                    break;
                }
            }
            //////////////////////////////////////////
        }
        count_function = 0;
        brightness = max;
        tripleZ_network_sendtext("ceedlerOutLight","on");
        analogWrite(Light_port,brightness);
    }
    else
    {
        while(soundlevel < max)
        {
            soundlevel++;
            analogWrite(Sound_port,(int)(soundlevel/SOUND_DOWN));
            analogWrite(TV_port,soundlevel);
            delay(delay_time_sound);
            //////////////////////////////////////////
            count_function += count_time_function;
            if(count_function > 1000)
            {
                //do sth
                check_do_function_sound();
                delay(50);
                keep = -1;
                count_function = 0;
                if(check_update)
                {
                    check_update = !check_update;
                    break;
                }
            }
            //////////////////////////////////////////
        }
        count_function = 0;
        soundlevel = max;
        tripleZ_network_sendtext("ceedlerOutTV","on");
        analogWrite(Sound_port,(int)(soundlevel/SOUND_DOWN));
    }
}
void lightAndSound_decrease(int time,int min,String Object)
{
    if(Object == "light")
    {
        keep = tripleZ_network_readtext("ceedlerOutRangeLight").toInt();
    }
    else
    {
        keep = tripleZ_network_readtext("ceedlerOutTV").toInt();
    }
    int delay_time_light = (time*1000)/(brightness-min);
    int delay_time_sound = (time*1000)/(soundlevel-min);
    int count_time_function;
    if(Object == "light")
    {
        count_time_function = 1000/delay_time_light;
    }
    else
    {
        count_time_function = 1000/delay_time_sound;
    } 
    int count_function = 0;
    if(Object == "light")
    {
        while(brightness > min)
        {
            brightness--;
            analogWrite(Light_port,brightness);
            delay(delay_time_light);
            //////////////////////////////////////////
            count_function += count_time_function;
            if(count_function > 1000)
            {
                //do sth
                check_do_function_light();
                delay(50);
                keep = -1;
                count_function = 0;
                if(check_update)
                {
                    check_update = !check_update;
                    break;
                }
            }
            //////////////////////////////////////////
        }
        count_function = 0;
        brightness = min;
        tripleZ_network_sendtext("ceedlerOutLight","off");
        analogWrite(Light_port,brightness);
    }
    else
    {
        while(soundlevel > min)
        {
            soundlevel--;
            analogWrite(Sound_port,(int)(soundlevel/SOUND_DOWN));
            analogWrite(TV_port,soundlevel);
            delay(delay_time_sound);
            //////////////////////////////////////////
            count_function += count_time_function;
            if(count_function > 1000)
            {
                //do sth
                check_do_function_sound();
                delay(50);
                keep = -1;
                count_function = 0;
                if(check_update)
                {
                    check_update = !check_update;
                    break;
                }
            }
            //////////////////////////////////////////
        }
        soundlevel = min;
        tripleZ_network_sendtext("ceedlerOutTV","off");
        analogWrite(Sound_port,(int)(soundlevel/SOUND_DOWN));
        analogWrite(TV_port,soundlevel);
    }
}
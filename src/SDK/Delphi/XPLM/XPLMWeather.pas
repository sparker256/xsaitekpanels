{
   Copyright 2005-2022 Laminar Research, Sandy Barbour and Ben Supnik All
   rights reserved.  See license.txt for usage. X-Plane SDK Version: 4.0.0
}

UNIT XPLMWeather;
INTERFACE
{
   This provides access to the X-Plane 12 enhanced weather system.
   
   ALL FUNCTIONS RELATING TO UPDATING THE WEATHER ARE CURRENTLY EXPERIMENTAL,
   FOR EVALUATION.
   
   The API will be kept stable if at all possible during the evaluation
   period. The details of how the data is processed will change over time as
   the weather engine changes, even after the API is stabilised.
}

USES
    XPLMDefs;
   {$A4}
{$IFDEF XPLM400}
{___________________________________________________________________________
 * WEATHER ACCESS
 ___________________________________________________________________________}

   {
    XPLMWeatherInfoWinds_t
   }
TYPE
   XPLMWeatherInfoWinds_t = RECORD
     { Altitude MSL, meters.                                                      }
     alt_msl                  : Single;
     { Wind speed, meters/sec.  When setting, use a negative value to signify     }
     { 'undefined'.                                                               }
     speed                    : Single;
     { Direction (true)                                                           }
     direction                : Single;
     { Gust speed, meters/sec. Total speed, not increase above wind speed.        }
     gust_speed               : Single;
     { Shear arc, degrees i.e. 50% of this arc in either direction from base      }
     shear                    : Single;
     { Clear-air turbulence ratio                                                 }
     turbulence               : Single;
   END;
   PXPLMWeatherInfoWinds_t = ^XPLMWeatherInfoWinds_t;

   {
    XPLMWeatherInfoClouds_t
   }
   XPLMWeatherInfoClouds_t = RECORD
     { Cloud type, float enum                                                     }
     cloud_type               : Single;
     { Coverage ratio                                                             }
     coverage                 : Single;
     { Altitude MSL, meters                                                       }
     alt_top                  : Single;
     { Altitude MSL, meters                                                       }
     alt_base                 : Single;
   END;
   PXPLMWeatherInfoClouds_t = ^XPLMWeatherInfoClouds_t;

CONST
    { The number of wind layers that are expected in the latest version of       }
    { XPLMWeatherInfo_t .                                                        }
   XPLM_NUM_WIND_LAYERS = 13;

    { The number of cloud layers that are expected in the latest version of      }
    { XPLMWeatherInfo_t .                                                        }
   XPLM_NUM_CLOUD_LAYERS = 3;

{$IFDEF XPLM420}
CONST
    { The number of temperature layers that are expected in the latest version of}
    { XPLMWeatherInfo_t .                                                        }
   XPLM_NUM_TEMPERATURE_LAYERS = 13;
{$ENDIF XPLM420}

{$IFDEF XPLM420}
    { Use this value to designate a wind layer as undefined when setting.        }
   XPLM_WIND_UNDEFINED_LAYER = -1;
{$ENDIF XPLM420}

{$IFDEF XPLM420}
    { Default radius of weather data points set using XPLMSetWeatherAtLocation   }
    { and XPLMSetWeatherAtAirport.                                               }
   XPLM_DEFAULT_WXR_RADIUS_NM = 30;
{$ENDIF XPLM420}

{$IFDEF XPLM420}
    { Default vertical radius of effect of weather data points set using         }
    { XPLMSetWeatherAtLocation and XPLMSetWeatherAtAirport.                      }
   XPLM_DEFAULT_WXR_RADIUS_MSL_FT = 10000;
{$ENDIF XPLM420}

   {
    XPLMWeatherInfo_t
    
    Basic weather conditions at a specific point. To specify exactly what data
    you intend to send or receive, it is required to set the structSize
    appropriately.
    
    Version 2 data starts at "temp_layers".
   }
TYPE
   XPLMWeatherInfo_t = RECORD
     { The size of the struct. Required for both reading and writing.             }
     structSize               : Integer;
     { Temperature at the given altitude in Celsius                               }
     temperature_alt          : Single;
     { Dewpoint at the given altitude in Celsius                                  }
     dewpoint_alt             : Single;
     { Pressure at the given altitude in Pascals. Pass 0 when setting to use      }
     { sea-level pressure instead of QNH.                                         }
     pressure_alt             : Single;
     { Precipitation rate at the given altitude. Unused when setting.             }
     precip_rate_alt          : Single;
     { Wind direction at the given altitude. Unused when setting.                 }
     wind_dir_alt             : Single;
     { Wind speed at the given altitude, meters/sec. Unused when setting.         }
     wind_spd_alt             : Single;
     { Turbulence ratio at the given altitude. Unused when setting.               }
     turbulence_alt           : Single;
     { Height of water waves in meters                                            }
     wave_height              : Single;
     { Length of water waves in meters. Unused when setting.                      }
     wave_length              : Single;
     { Direction from which water waves are coming                                }
     wave_dir                 : Integer;
     { Speed of wave advance in meters/sec. Unused when setting.                  }
     wave_speed               : Single;
     { Base visibility at 0 altitude, meters                                      }
     visibility               : Single;
     { Base precipitation ratio at 0 altitude                                     }
     precip_rate              : Single;
     { Climb rate due to thermals, meters/sec                                     }
     thermal_climb            : Single;
     { Pressure at sealevel in Pascals. Used when setting ONLY if pressure_alt    }
     { (i.e. QNH) is not valid.                                                   }
     pressure_sl              : Single;
     { Defined wind layers. Not all layers are always defined.                    }
     wind_layers[XPLM_NUM_WIND_LAYERS]: XPLMWeatherInfoWinds_t;
     { Defined cloud layers. Not all layers are always defined.                   }
     cloud_layers[XPLM_NUM_CLOUD_LAYERS]: XPLMWeatherInfoClouds_t;
{$IFDEF XPLM420}
     { Temperatures at altitude, in degrees C. Layer altitudes are the same       }
     { globally - see the 'sim/weather/region/atmosphere_alt_levels_m' dataref.   }
     temp_layers[XPLM_NUM_TEMPERATURE_LAYERS]: Single;
{$ENDIF XPLM420}
{$IFDEF XPLM420}
     { Dewpoints at altitude, in degrees C. Layer altitudes are the same globally }
     { - see the 'sim/weather/region/atmosphere_alt_levels_m' dataref.            }
     dewp_layers[XPLM_NUM_TEMPERATURE_LAYERS]: Single;
{$ENDIF XPLM420}
{$IFDEF XPLM420}
     { The altitude in MSL of the troposphere.                                    }
     troposphere_alt          : Single;
{$ENDIF XPLM420}
{$IFDEF XPLM420}
     { The temperature in degrees C of the troposphere.                           }
     troposphere_temp         : Single;
{$ENDIF XPLM420}
{$IFDEF XPLM420}
     { Age in seconds of this weather report. Age affects how strongly the report }
     { affects the resulting weather.                                             }
     age                      : Single;
{$ENDIF XPLM420}
{$IFDEF XPLM420}
     { Horizontal radius of effect of this weather report, nautical miles.        }
     radius_nm                : Single;
{$ENDIF XPLM420}
{$IFDEF XPLM420}
     { Vertical radius of effect of this weather report, feet MSL.                }
     max_altitude_msl_ft      : Single;
{$ENDIF XPLM420}
   END;
   PXPLMWeatherInfo_t = ^XPLMWeatherInfo_t;

   {
    XPLMGetMETARForAirport
    
    Get the last-downloaded METAR report for an airport by ICAO code. Note that
    the actual weather at that airport may have evolved significantly since the
    last downloaded METAR. outMETAR must point to a char buffer of at least 150
    characters. THIS CALL DOES NOT RETURN THE CURRENT WEATHER AT THE AIRPORT,
    and returns an empty string if the system is not in real-weather mode.
    
    This call is not intended to be used per-frame.
   }
   PROCEDURE XPLMGetMETARForAirport(
                                        airport_id          : XPLMString;
                                        outMETAR            : PXPLMFixedString150_t);
    cdecl; external XPLM_DLL;

   {
    XPLMGetWeatherAtLocation
    
    Get the current weather conditions at a given location. Note that this does
    not work world-wide, only within the surrounding region. Return 1 if
    detailed weather (i.e. an airport-specific METAR) was found, 0 if not. In
    both cases, the structure will contain the best data available.
    
    This call is not intended to be used per-frame.
   }
   FUNCTION XPLMGetWeatherAtLocation(
                                        latitude            : Real;
                                        longitude           : Real;
                                        altitude_m          : Real;
                                        out_info            : PXPLMWeatherInfo_t) : Integer;
    cdecl; external XPLM_DLL;

{$IFDEF XPLM420}
   {
    XPLMBeginWeatherUpdate
    
    Inform the simulator that you are starting a batch update of weather
    information. If you are providing multiple weather updates, using this call
    may improve performance by telling the simulator not to update weather
    until you are done.
    
    This call is not intended to be used per-frame.
   }
   PROCEDURE XPLMBeginWeatherUpdate;
    cdecl; external XPLM_DLL;
{$ENDIF XPLM420}

{$IFDEF XPLM420}
   {
    XPLMEndWeatherUpdate
    
    Inform the simulator that you are ending a batch update of weather
    information. If you have called XPLMBeginWeatherUpdate, you MUST call
    XPLMEndWeatherUpdate before exiting your callback otherwise any accumulated
    weather data will be discarded.
    
    When using incremental mode, any changes made are applied to your existing
    data. This makes it possible to only update a fraction of your weather data
    at any one time. When not using incremental mode, ALL reports previously
    passed by your plugin are erased before applying new data.
    
    When using any of these 'weather set' APIs, the normal mode of operation is
    that you are setting the weather in the near future. Currently this is
    somewhere between one and two minutes but do not rely on this remaining the
    same.
    
    Setting future weather ensures that there is no sudden jump in weather
    conditions when you make a change mid-cycle. In some situations, notably
    for an initial setup, you may want to ensure that the weather is changed
    instantly. To do this, set 'updateImmediately' as true.
    
    This call is not intended to be used per-frame.
   }
   PROCEDURE XPLMEndWeatherUpdate(
                                        isIncremental       : Integer;
                                        updateImmediately   : Integer);
    cdecl; external XPLM_DLL;
{$ENDIF XPLM420}

{$IFDEF XPLM420}
   {
    XPLMSetWeatherAtLocation
    
    Set the current weather conditions at a given location. Please see the
    notes on individual fields in XPLMSetWeatherAtAirport, and notes on timing
    in XPLMEndWeatherUpdate.
    
    This call is not intended to be used per-frame.
   }
   PROCEDURE XPLMSetWeatherAtLocation(
                                        latitude            : Real;
                                        longitude           : Real;
                                        altitude_m          : Real;
                                        in_info             : PXPLMWeatherInfo_t);
    cdecl; external XPLM_DLL;
{$ENDIF XPLM420}

{$IFDEF XPLM420}
   {
    XPLMEraseWeatherAtLocation
    
    Erase weather conditions set by your plugin at a given location. You must
    give exactly the same coordinates that you used to create a weather record
    at this point. It does NOT mean 'create clear weather at this location'.
    
    This call is not intended to be used per-frame.
   }
   PROCEDURE XPLMEraseWeatherAtLocation(
                                        latitude            : Real;
                                        longitude           : Real);
    cdecl; external XPLM_DLL;
{$ENDIF XPLM420}

{$IFDEF XPLM420}
   {
    XPLMSetWeatherAtAirport
    
    Set the current weather conditions at a given airport. Unlike
    XPLMSetWeatherAtLocation, this call will replace any existing weather
    records for that airport from other sources (i.e. downloaded METARs)
    instead of being used as just another weather sample.
    
    Some notes on individual fields:
      - pressure_alt should be QNH as reported by a station at the ground
        altitude given, or 0 if you are passing sealevel pressure in
        'pressure_sl' instead.
      - pressure_sl is ignored if pressure_alt is given.
      - wind_dir_alt, wind_spd_alt, turbulence_alt, wave_speed, wave_length are
        derived from other data and are UNUSED when setting weather.
      - Temperatures can be given either as a single temperature at the ground
        altitude (temperature_alt) OR as an array of temperatures aloft
        (temp_layers), if the struct is V2 or higher. If you wish to use the V2
        struct and still provide a single ground-level temperature, pass -100
        or lower as the first element of the temp_layers array. In this case,
        existing weather at that point will be used for temperatures at
        altitude.
      - The same rules apply to dewpoint temperatures; either a single value at
        ground level in 'dewpoint_alt', or per-layer values in 'dewp_layers'.
      - The troposphere altitude and temperature will be derived from existing
        data if you pass 0 or lower for troposphere_alt.
    
    This call is not intended to be used per-frame.
   }
   PROCEDURE XPLMSetWeatherAtAirport(
                                        airport_id          : XPLMString;
                                        in_info             : PXPLMWeatherInfo_t);
    cdecl; external XPLM_DLL;
{$ENDIF XPLM420}

{$IFDEF XPLM420}
   {
    XPLMEraseWeatherAtAirport
    
    Erase the current weather conditions set by your plugin at a given airport,
    allowing records from other sources to be used. It does NOT mean 'create
    clear weather at this airport'.
    
    This call is not intended to be used per-frame.
   }
   PROCEDURE XPLMEraseWeatherAtAirport(
                                        airport_id          : XPLMString);
    cdecl; external XPLM_DLL;
{$ENDIF XPLM420}

{$ENDIF XPLM400}

IMPLEMENTATION

END.

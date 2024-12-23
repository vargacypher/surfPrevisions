import pysurfline
import pandas as pd
from datetime import datetime as dt

class DailySurf:
    def __init__(self,**kwargs):
        self.dt_coleted = kwargs['dt_coleted']
        self.surf_waves_min = kwargs['surf_waves_min']
        self.surf_waves_max = kwargs['surf_waves_max']
        self.probability = kwargs['probability']
        self.wind_direction = kwargs['wind_direction']
        self.wind_speed = kwargs['wind_speed']
        self.general_temp = kwargs['general_temp']
        self.max_tideshigh = kwargs['max_tideshigh']
        self.timestamp_max_tideshigh = kwargs['timestamp_max_tideshigh']
        self.min_tideslow = kwargs['min_tideslow']
        self.timestamp_min_tideslow = kwargs['timestamp_min_tideslow']


def generate_data(spotId:str):

    '''
    '''
    today = dt.now().strftime('%Y-%m-%d')

    spotforecasts = pysurfline.get_spot_forecasts(
        spotId,
        days = 1
    )

    #GENERAL DATA LAST HOUR FROM SURFLINE
    general_df = spotforecasts.get_dataframe()
    general_df['timestamp_dt'] = general_df['timestamp_dt']
    current_hour = dt.now().hour
    general_df = general_df[general_df['timestamp_dt'].dt.hour == current_hour]
    
    general_df = general_df.head(1)[
            [
                'timestamp_dt',
                'utcOffset',
                'surf_min',
                'surf_max',
                'probability',
                'temperature',
                'condition',
                'speed',
                'direction'
            ]                
        ].to_dict('records')

    #TIDES
    tide_df = spotforecasts.get_dataframe('tides')
    # Filter tide_df for the last 12 hours
    current_time = dt.now()
    cutoff_time = current_time - timedelta(hours=12)
    tide_df = tide_df[tide_df['timestamp_dt'] >= cutoff_time]
    tide_df['timestamp_dt'] = tide_df['timestamp_dt'].dt.hour
    tide_df['timestamp_dt'] = tide_df['timestamp_dt'].astype(str)

    del spotforecasts
    
    tide_max = tide_df[(tide_df['height'] == tide_df['height'].max())].head(1)
    tide_max = tide_max[['timestamp_dt','height']].to_dict('records')

    tide_min = tide_df[(tide_df['height'] == tide_df['height'].min())].head(1)
    tide_min = tide_min[['timestamp_dt','height']].to_dict('records')
    del tide_df

    surf_data = DailySurf(
        dt_coleted = general_df[0]['timestamp_dt'],
        surf_waves_min = round(general_df[0]['surf_min'],2),
        # surf_waves_min = round((general_df[0]['surf_min']*30.48)/100,2),
        surf_waves_max =  '-'.join([str(round(general_df[0]['surf_min'],2)),str(round(general_df[0]['surf_max'],2))]), #Feet to cm
        # surf_waves_max =  '-'.join([str(round((general_df[0]['surf_min']*30.48)/100,2)),str(round((general_df[0]['surf_max']*30.48)/100,2))]), #Feet to cm
        probability = general_df[0]['probability'],
        wind_direction = general_df[0]['direction'],
        wind_speed = str(general_df[0]['speed']),
        general_temp = str(round(general_df[0]['temperature'] , 2)), # Fahrenheit Celsius
        # general_temp = str(round((general_df[0]['temperature'] - 32) / 1.8, 2)), # Fahrenheit Celsius
        max_tideshigh = str(round(tide_max[0]['height'],2)), #Feet to cm
        # max_tideshigh = str(round((tide_max[0]['height']*30.48)/100,2)), #Feet to cm
        timestamp_max_tideshigh = tide_max[0]['timestamp_dt'],
        min_tideslow = str(round(tide_min[0]['height'],2)), #Feet to cm
        # min_tideslow = str(round((tide_min[0]['height']*30.48)/100,2)), #Feet to cm
        timestamp_min_tideslow = tide_min[0]['timestamp_dt']
    )

    return surf_data
import pandas as pd
import numpy as np
from statsmodels.tsa.stattools import coint
import warnings
warnings.filterwarnings('ignore')

def get_coin_metadata():
    return {
        "target": {"symbol": "LDO", "timeframe": "1H"},
        "anchors": [
            {"symbol": "BTC", "timeframe": "1H"},
            {"symbol": "ETH", "timeframe": "1H"}
        ]
    }

def generate_signals(candles_target: pd.DataFrame, candles_anchor: pd.DataFrame) -> pd.DataFrame:
    metadata = get_coin_metadata()
    target_symbol = metadata["target"]["symbol"]
    anchors = [a["symbol"] for a in metadata["anchors"]]
    
    # Merge data
    df = candles_target.copy()
    for anchor in anchors:
        prefix_cols = [col for col in candles_anchor.columns if col.startswith(anchor.lower())]
        df = df.merge(candles_anchor[prefix_cols], left_index=True, right_index=True, how='inner')
    
    # Cointegration test and signals
    signals = pd.DataFrame(index=df.index, columns=['signal'], data='HOLD')
    
    for anchor in anchors:
        close_anchor = df[f'close_{anchor.lower()}']
        close_target = df[target_symbol.lower()]
        
        # Test cointegration
        score, pvalue, _ = coint(close_target, close_anchor)
        if pvalue < 0.05:  # Cointegrated pair
            ratio = close_target / close_anchor
            mean_ratio = ratio.rolling(20).mean()
            std_ratio = ratio.rolling(20).std()
            
            zscore = (ratio - mean_ratio) / std_ratio
            signals[zscore > 2] = 'SELL'
            signals[zscore < -2] = 'BUY'
    
    return signals

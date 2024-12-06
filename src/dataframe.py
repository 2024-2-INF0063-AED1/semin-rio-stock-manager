import pandas as pd
import random

# Função para gerar o CSV com quantidade personalizada de dados aleatórios
def gerar_dados_aleatorios(n):
    dados = {
        "NP": [random.randint(1, 200) for _ in range(n)],  # Números de Pedido aleatórios entre 1 e 200
        "Distancia": [round(random.uniform(10.0, 100.0), 2) for _ in range(n)],  # Distâncias entre 10.0 e 100.0 km
        "DataEntrega": [
            int(f"{random.randint(2024, 2027)}{random.randint(1, 12):02}{random.randint(1, 28):02}")
            for _ in range(n)
        ],  # Data de entrega aleatória no formato AAAAMMDD
    }
    
    df = pd.DataFrame(dados)
    return df

# Solicitar ao usuário a quantidade de dados desejados
quantidade_dados = int(input("Digite a quantidade de dados a ser gerada: "))

# Gerar os dados com a quantidade solicitada
df_gerado = gerar_dados_aleatorios(quantidade_dados)

# Salvar o DataFrame em um arquivo CSV
output_path = f"dados_aleatorios.csv"
df_gerado.to_csv(output_path, index=False)

# Exibir o DataFrame gerado
print(f"Arquivo CSV com {quantidade_dados} registros gerado: {output_path}")
print(df_gerado)

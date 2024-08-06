import os
import json
import sys
import platform

def getJars(minecraftDir, version):
    jsonFilePath = os.path.join(minecraftDir, 'versions', version, f'{version}.json')

    with open(jsonFilePath, 'r') as jsonFile:
        jsonFileKeys = json.load(jsonFile)

    jars = []
    for x in jsonFileKeys['libraries']:
        jarFileParts = x['name'].split(':')
        jarFile = os.path.join(minecraftDir, 'libraries', 
                               jarFileParts[0].replace('.', '/'), jarFileParts[1], jarFileParts[2], 
                               f'{jarFileParts[1]}-{jarFileParts[2]}.jar')
        jars.append(jarFile)
    
    if 'inheritsFrom' in jsonFileKeys:
        jars.extend(getJars(minecraftDir, jsonFileKeys['inheritsFrom']))

    return ':'.join(jars)
def getForgeJars(minecraftDir, forge_version):
    jars = []
    try:
        ForgePath = os.path.join(minecraftDir, 'libraries/net/minecraftforge/forge', forge_version)
        # 获取目录中的所有文件和文件夹
        files_and_dirs = os.listdir(ForgePath)
        # 仅保留文件，排除文件夹
        files = [f for f in files_and_dirs if os.path.isfile(os.path.join(ForgePath, f))]
        for x in files:
            jarFile = os.path.join(ForgePath, x)
            jars.append(jarFile)
        
        return ':'.join(jars)
    except Exception as e:
        print(f"An error occurred: {e}")
        return []


def check_features(features):
    return all(value for value in features.values())

def getLowerMinecraftArgvs(minecraftDir, version, ID):
    jsonFilePath = os.path.join(minecraftDir, 'versions', version, f'{version}.json')
    # print(jsonFilePath)

    with open(jsonFilePath, 'r') as jsonFile:
        jsonFileKeys = json.load(jsonFile)

    argvs = []
    if 'minecraftArguments' in jsonFileKeys:
        # 使用旧的字符串式参数配置(低版本)
        argvs.append(jsonFileKeys['minecraftArguments'])
    else:
        # 新的列表式参数配置(高版本)
        for item in jsonFileKeys['arguments']['game']:
            if isinstance(item, str):
                argvs.append(item)
            elif isinstance(item, dict) and 'value' in item:
                # 处理可能存在的规则和值
                if all(check_features(rule['features']) for rule in item['rules']):
                    # 如果所有规则都通过，则添加参数
                    argvs.extend(item['value'])

    argvs_str = ' '.join(argvs)
    argvs_str = argvs_str.replace('${auth_player_name}', ID)\
                         .replace('${version_name}', version)\
                         .replace('${game_directory}', minecraftDir)\
                         .replace('${assets_root}', os.path.join(minecraftDir, 'assets'))\
                         .replace('${assets_index_name}', jsonFileKeys['assets'])\
                         .replace('${user_type}', 'offline')\
                         .replace('${version_type}', jsonFileKeys['type'])\
                         .replace('${clientid}', 'YourClientIdHere')\
                         .replace('${resolution_width}', '1920')\
                         .replace('${resolution_height}', '1080')\
                         .replace('${quickPlayPath}', '/path/to/quickplay')\
                         .replace('${quickPlaySingleplayer}', 'singleplayer_mode')\
                         .replace('${quickPlayMultiplayer}', 'multiplayer_mode')\
                         .replace('${quickPlayRealms}', 'realms_mode')\
                         .replace('${auth_access_token}', 'dummy')\
                         .replace('${auth_uuid}', '00000000-0000-0000-0000-000000000000')\
                         .replace('${user_properties}', ' ')
    return f"{jsonFileKeys['mainClass']} {argvs_str}"
def main():
    MinecraftDir = './.minecraft'
    Version = ''
    maxMen = '2048m'
    ID = ''
    job = 0
    theUsageText = (f'Usage:\t\t{sys.argv[0]} [-d Minecraft_dir] [-v version] [-m 2048m] Username\n'
                    f'\t\t\tLaunch Minecraft\n\n'
                    f'\t\t{sys.argv[0]} [-d Minecraft_dir] -l\n\t\t\tList Minecraft versions')

    if len(sys.argv) == 1:
        print(theUsageText)
        sys.exit()
    else:
        t = 1
        while t < len(sys.argv):
            if sys.argv[t] == '-d':
                t += 1
                MinecraftDir = sys.argv[t]
            elif sys.argv[t] == '-v':
                t += 1
                Version = sys.argv[t]
            elif sys.argv[t] == '-m':
                t += 1
                maxMen = sys.argv[t]
            elif sys.argv[t] == '-h':
                print(theUsageText)
                sys.exit()
            elif sys.argv[t] == '-l':
                job = 1
            else:
                ID = sys.argv[t]
            t += 1

    if job == 1:
        print('我的世界版本文件夹:')
        versions = os.listdir(os.path.join(MinecraftDir, 'versions'))
        versions.sort(reverse=True)
        for version in versions:
            print(f'\t{version}')
        sys.exit()

    if ID == '':
        print(theUsageText)
        sys.exit()

    if Version == '':
        versions = os.listdir(os.path.join(MinecraftDir, 'versions'))
        versions.sort(reverse=True)
        Version = versions[0]
    #低版本加-Xincgc这个配置
        
    system = platform.system()
    if system == "Linux":
        before = (
            f'java '
            f'-Dorg.lwjgl.util.Debug=true '
            f'-Dorg.lwjgl.util.DebugLoader=true '
            f'-XX:-UseAdaptiveSizePolicy '
            f'-XX:-OmitStackTraceInFastThrow '
            f'-Xmn128m '
            f'-Xmx{maxMen} '
            f'-Djava.library.path={os.path.join(MinecraftDir, "versions", Version, "natives-linux-x86_64")} '
            f'-Dfml.ignoreInvalidMinecraftCertificates=true '
            f'-Dfml.ignorePatchDiscrepancies=true '
            f'-Duser.home=/ '
            f'-cp "'
        )
    elif system == "Windows":
                before = (
            f'java '
            f'-Dorg.lwjgl.util.Debug=true '
            f'-Dorg.lwjgl.util.DebugLoader=true '
            f'-XX:-UseAdaptiveSizePolicy '
            f'-XX:-OmitStackTraceInFastThrow '
            f'-Xmn128m '
            f'-Xmx{maxMen} '
            f'-Djava.library.path={os.path.join(MinecraftDir, "versions", Version, "natives-linux-x86_64")} '
            f'-Dfml.ignoreInvalidMinecraftCertificates=true '
            f'-Dfml.ignorePatchDiscrepancies=true '
            f'-Duser.home=/ '
            f'-cp "'
        )
    jars = getJars(MinecraftDir, Version)


    jars += f':{os.path.join(MinecraftDir, "versions", Version, f"{Version}.jar")}' 


    forge_jars = getForgeJars(MinecraftDir, '1.20.4-49.1.4')

    jars += f':{forge_jars}"'
    after = getLowerMinecraftArgvs(MinecraftDir, Version, ID)

    cmd = before + jars + " " + after
    
    



    os.system(cmd)    

if __name__ == "__main__":
    main()

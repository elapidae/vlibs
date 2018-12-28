# coding=utf-8
import jinja2
import argparse
import glob, os

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument('vlib_name')
    arg_vlib_name = parser.parse_args().vlib_name
    print(arg_vlib_name)


    # input = "../"+arg_vlib_name+"/"+arg_vlib_name+".cmake"
    inputs=["../"+arg_vlib_name+"/"+arg_vlib_name+".cmake", "../"+arg_vlib_name+"/"+arg_vlib_name+".pri"]


    # data = open(input).read()

    # manual = ""
    #
    # with open(input, "r") as infile:
    #     copy = False
    #     for line in infile:
    #         if line.lstrip().startswith("#<"):
    #             copy = True
    #         elif line.lstrip().startswith("#>"):
    #             break
    #         elif copy:
    #             manual += line
    #
    # print(manual)

    templateLoader = jinja2.FileSystemLoader(searchpath="./")
    templateEnv = jinja2.Environment(loader=templateLoader)

    sources_c = [os.path.basename(x) for x in glob.glob("../"+arg_vlib_name+"/*.c")]
    sources_cpp = [os.path.basename(x) for x in glob.glob("../"+arg_vlib_name+"/*.cpp")]
    sources = sources_c + sources_cpp
    print(sources)

    headers_h = [os.path.basename(x) for x in glob.glob("../"+arg_vlib_name+"/*.h")]
    headers_hpp = [os.path.basename(x) for x in glob.glob("../"+arg_vlib_name+"/*.hpp")]
    headers = headers_h + headers_hpp
    print(headers)


    tm = ["template.cmake", "template.pri"]

    for i in range(2):
        cmake_template_file = tm[i]
        try:
            template = templateEnv.get_template(cmake_template_file)
        except jinja2.exceptions.TemplateNotFound:
            print("Шаблон ", tm[i], "не найден")
            exit()

        manual = ""

        try:
            file = open(inputs[i], 'r')
        except FileNotFoundError:
            file = open(inputs[i], 'w')

        with open(inputs[i], "r") as infile:
            copy = False
            for line in infile:
                if line.lstrip().startswith("#<<< Start your code here"):
                    copy = True
                elif line.lstrip().startswith("#>>> Stop your code here"):
                    break
                elif copy:
                    manual += line

        print(manual)

        outputText = template.render(vlib_name=arg_vlib_name, manual_code=manual, sources=sources, headers=headers)


        with open(inputs[i], "w") as fh:
            fh.write(outputText)









webtalk_init -webtalk_dir E:/codehub/OpenMIPS_without_ddr/OpenMIPS/OpenMIPS.sim/sim_1/behav/xsim/xsim.dir/openmips_min_sopc_tb_behav/webtalk/
webtalk_register_client -client project
webtalk_add_data -client project -key date_generated -value "Sat May 15 00:19:28 2021" -context "software_version_and_target_device"
webtalk_add_data -client project -key product_version -value "XSIM v2019.1 (64-bit)" -context "software_version_and_target_device"
webtalk_add_data -client project -key build_version -value "2552052" -context "software_version_and_target_device"
webtalk_add_data -client project -key os_platform -value "WIN64" -context "software_version_and_target_device"
webtalk_add_data -client project -key registration_id -value "" -context "software_version_and_target_device"
webtalk_add_data -client project -key tool_flow -value "xsim_vivado" -context "software_version_and_target_device"
webtalk_add_data -client project -key beta -value "FALSE" -context "software_version_and_target_device"
webtalk_add_data -client project -key route_design -value "FALSE" -context "software_version_and_target_device"
webtalk_add_data -client project -key target_family -value "not_applicable" -context "software_version_and_target_device"
webtalk_add_data -client project -key target_device -value "not_applicable" -context "software_version_and_target_device"
webtalk_add_data -client project -key target_package -value "not_applicable" -context "software_version_and_target_device"
webtalk_add_data -client project -key target_speed -value "not_applicable" -context "software_version_and_target_device"
webtalk_add_data -client project -key random_id -value "4a3248a9-a069-4bbc-8d9c-512d1f707b70" -context "software_version_and_target_device"
webtalk_add_data -client project -key project_id -value "4c9d15a03076431c966d8e493222eb77" -context "software_version_and_target_device"
webtalk_add_data -client project -key project_iteration -value "210" -context "software_version_and_target_device"
webtalk_add_data -client project -key os_name -value "Windows Server 2016 or Windows 10" -context "user_environment"
webtalk_add_data -client project -key os_release -value "major release  (build 9200)" -context "user_environment"
webtalk_add_data -client project -key cpu_name -value "Intel(R) Core(TM) i5-6500 CPU @ 3.20GHz" -context "user_environment"
webtalk_add_data -client project -key cpu_speed -value "3192 MHz" -context "user_environment"
webtalk_add_data -client project -key total_processors -value "1" -context "user_environment"
webtalk_add_data -client project -key system_ram -value "17.000 GB" -context "user_environment"
webtalk_register_client -client xsim
webtalk_add_data -client xsim -key Command -value "xsim" -context "xsim\\command_line_options"
webtalk_add_data -client xsim -key trace_waveform -value "true" -context "xsim\\usage"
webtalk_add_data -client xsim -key runtime -value "24505001 ps" -context "xsim\\usage"
webtalk_add_data -client xsim -key iteration -value "4" -context "xsim\\usage"
webtalk_add_data -client xsim -key Simulation_Time -value "45.12_sec" -context "xsim\\usage"
webtalk_add_data -client xsim -key Simulation_Memory -value "76456_KB" -context "xsim\\usage"
webtalk_transmit -clientid 3841963930 -regid "" -xml E:/codehub/OpenMIPS_without_ddr/OpenMIPS/OpenMIPS.sim/sim_1/behav/xsim/xsim.dir/openmips_min_sopc_tb_behav/webtalk/usage_statistics_ext_xsim.xml -html E:/codehub/OpenMIPS_without_ddr/OpenMIPS/OpenMIPS.sim/sim_1/behav/xsim/xsim.dir/openmips_min_sopc_tb_behav/webtalk/usage_statistics_ext_xsim.html -wdm E:/codehub/OpenMIPS_without_ddr/OpenMIPS/OpenMIPS.sim/sim_1/behav/xsim/xsim.dir/openmips_min_sopc_tb_behav/webtalk/usage_statistics_ext_xsim.wdm -intro "<H3>XSIM Usage Report</H3><BR>"
webtalk_terminate

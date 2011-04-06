require "bundler"
Bundler::GemHelper.install_tasks
require "./lib/ceedling"
require "fileutils"
require "erb"

desc "update all the tools from sourceforge and update version info"
task :update_tools do

  puts "\nRetrieving ceedling content from SourceForge..."
  rm_rf "temp"
  mkdir "temp"
  cd "temp" do
    svn_checkout_command = 'svn co http://ceedling.svn.sourceforge.net/svnroot/ceedling/trunk .'
    puts svn_checkout_command
    `#{svn_checkout_command}`
    rm_rf Dir["./**/.svn/"], :verbose => false # remove svn artifacts
  end

  # define mapping for pruning content from sourceforge
  mapping = [
    {:src => 'lib/',                                             :dest => ''},
    {:src => 'plugins/',                                         :dest => ''},
    {:src => 'release/',                                         :dest => ''},
    {:src => 'vendor/c_exception/lib/',                          :dest => 'vendor/c_exception/'},
    {:src => 'vendor/c_exception/release/',                      :dest => 'vendor/c_exception/'},
    {:src => 'vendor/cmock/config/',                             :dest => 'vendor/cmock/'},
    {:src => 'vendor/cmock/lib/',                                :dest => 'vendor/cmock/'},
    {:src => 'vendor/cmock/release/',                            :dest => 'vendor/cmock/'},
    {:src => 'vendor/cmock/src/',                                :dest => 'vendor/cmock/'},
    {:src => 'vendor/constructor/lib/',                          :dest => 'vendor/constructor/'},
    {:src => 'vendor/deep_merge/lib/',                           :dest => 'vendor/deep_merge/'},
    {:src => 'vendor/diy/lib',                                   :dest => 'vendor/diy/'},
    {:src => 'vendor/unity/release/',                            :dest => 'vendor/unity/'},
    {:src => 'vendor/unity/src/',                                :dest => 'vendor/unity/'},
    {:src => 'vendor/c_exception/docs/CExceptionSummary.pdf',    :dest => 'docs/', :is_file => true},
    {:src => 'vendor/cmock/docs/CMock Summary.pdf',              :dest => 'docs/', :is_file => true},
    {:src => 'docs/Ceedling Packet.pdf',                         :dest => 'docs/', :is_file => true},
    {:src => 'vendor/unity/docs/Unity Summary.pdf',              :dest => 'docs/', :is_file => true},
  ]

  puts "\nUpdating tools with the latest goods..."
  rm_rf "new_project_template/vendor/**"
  mapping.each do |path|
    dest = "new_project_template/vendor/ceedling/#{path[:dest]}"
    dir = dest.sub(/\w+$/, '')
    if !File.exist?(dir)
      mkdir_p dest
    end
    puts "temp/#{path[:src]} -> #{dest}"
    FileUtils.cp_r "temp/#{path[:src]}", "#{dest}"
  end
  rm_rf "temp"

  puts "\nUpdating version info..."
  versions = {}
  full_version_info = nil
  Dir.chdir(Ceedling::NEW_PROJECT_DIR) { full_version_info = `rake version` }
  puts full_version_info
  full_version_info.each_line do |line|
    line = line.split("::")
    versions[line.first.strip.upcase] = line.last.strip
  end
  result = ERB.new(File.read("lib/ceedling/version.rb.erb")).result(binding)
  File.open("lib/ceedling/version.rb", "wb+") { |f| f.puts result }

end
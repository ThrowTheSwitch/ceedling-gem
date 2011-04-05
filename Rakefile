require 'bundler'
Bundler::GemHelper.install_tasks
require "./lib/ceedling"
require "fileutils"

desc "update ceedling versions in gem; assumes ceedling up-to-date"
task :update_versions do
  versions = {}
  # There's an extra line of junk at the beginning, but who cares.
  full_version_info = nil
  Dir.chdir(Ceedling::NEW_PROJECT_DIR) { full_version_info = `rake version` }
  full_version_info.each_line do |line|
    line = line.split("::")
    versions[line.first.strip.upcase] = line.last.strip
  end
  require "erb"
  result = ERB.new(File.read("lib/ceedling/version.rb.erb")).result(binding)
  File.open("lib/ceedling/version.rb", "wb+") { |f| f.puts result }
end

desc "update ceedling, cmock, cexception and unity"
task :update_tools do

  rm_rf "temp"
  mkdir "temp"

  tools_versions = [
    {:path => ".",                 :revision => nil, :short_version => nil, :full_version => nil},
    {:path => "vendor/cmock",      :revision => nil, :short_version => nil, :full_version => nil},
    {:path => "vendor/unity",      :revision => nil, :short_version => nil, :full_version => nil},
    {:path => "vendor/c_exception", :revision => nil, :short_version => nil, :full_version => nil},
  ]

  cd "temp" do
    puts `svn co http://ceedling.svn.sourceforge.net/svnroot/ceedling/trunk .`
    tools_versions.each do |tool|
      cd tool[:path] do
        tool[:revision] = `svn info`.split("\n")[4].sub(/^Revision: +/, '')
        tool[:short_version] = File.readlines("release/version.info")[0].chomp
        tool[:full_version] = "#{tool[:short_version]}.#{tool[:revision]}"
        puts tool[:path], tool[:full_version]
      end
    end
    rm_rf Dir["./**/.svn/"], :verbose => false
  end

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

end